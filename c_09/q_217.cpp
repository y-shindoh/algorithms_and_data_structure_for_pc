/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_217.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.217の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  B: Binary Search Tree II (q_214.cppに該当) に、
  delete 命令を追加し、二分探索木Tに対し、
  以下の命令を実行するプログラムを作成してください。

  - insert k: Tにキーkを挿入する
  - find k: Tにキーkが存在するか否かを報告する。
  - delete k: キーkを持つ節点を削除する。
  - print: キーを木の中間順巡回と先行順巡回アルゴリズムで出力する。

  二分探索木Tから与えられたキーkを持つ節点zを削除する delete k は
  以下の場合を検討したアルゴリズムに従い、
  二分探索条件を保ちつつ親子のリンク (ポインタ) を更新します。

  1) zが子を持たない場合、zの親pの子 (つまりz) を削除する。

  2) zがちょうど1つの子を持つ場合、zの親の子をzの子に変更、
     zの子の親をzの親に変更し、zを木から削除する。

  3) zが子を2つ持つ場合、zの次節点yのキーをzのキーへコピーし、yを削除する。
     yの削除では、1または2を適用する。
     ここで、zの次節点とは、中間順巡回でzの次に得られる節点である。
 */

/*
  メモ:
  - メソッド名を delete にできないので、remove と変更した。
  - 上記3の処理は複雑になるので代替の処理を用いた。
 */

#include <cstdio>
#include <cassert>

/**
 * 二分木のクラス
 */
template<typename TYPE>
class Node
{
public:

	TYPE d_;			///< データ
	Node<TYPE>* c_[2];	///< 子

	/**
	 * コンストラクタ
	 * @param[in]	d	保持するデータ
	 */
	Node(const TYPE& d)
		: d_(d)
		{
			c_[0] = c_[1] = 0;
		}
};

/**
 * 二分探索木に新規ノードを追加
 * @param[in,out]	tree	二分探索木
 * @param[in,out]	node	追加する新規ノード
 * @return	追加後の二分探索木のルート
 */
template<typename TYPE>
Node<TYPE>*
insert(Node<TYPE>* tree,
	   Node<TYPE>* node)
{
	assert(node);

	if (!tree) return node;

	Node<TYPE>* n(tree);

	while ('-') {
		size_t i = (size_t)(node->d_ >= n->d_);
		if (n->c_[i]) {
			n = n->c_[i];
			continue;
		}
		n->c_[i] = node;
		return tree;
	}
}

/**
 * 二分探索木に新規値を追加
 * @param[in,out]	tree	二分探索木
 * @param[in,out]	key	追加する新規値
 * @return	追加後の二分探索木のルート
 */
template<typename TYPE>
Node<TYPE>*
insert(Node<TYPE>* tree,
	   const TYPE& key)
{
	return insert<TYPE>(tree, new Node<TYPE>(key));
}

/**
 * 二分探索木から値を削除
 * @param[in,out]	tree	二分探索木
 * @param[in,out]	key	削除する値
 * @return	削除後の二分探索木のルート
 */
template<typename TYPE>
Node<TYPE>*
remove(Node<TYPE>* tree,
	   const TYPE& key)
{
	if (!tree) return 0;

	if (key != tree->d_) {
		size_t i = (size_t)(key > tree->d_);
		tree->c_[i] = remove<TYPE>(tree->c_[i], key);
		return tree;
	}

	Node<TYPE>* node;

	if (tree->c_[1]) {
		node = tree->c_[1];
		if (tree->c_[0]) {
			Node<TYPE>* n(node);
			while (n->c_[0]) n = n->c_[0];
			n->c_[0] = tree->c_[0];
		}
	}
	else {
		node = tree->c_[0];
	}

	delete tree;
	return node;
}

/**
 * 二分探索木の値を探索
 * @param[in,out]	tree	二分探索木
 * @param[in,out]	key	探索する値
 * @return	追加後の二分探索木のルート (探索失敗時は 0 が返る)
 */
template<typename TYPE>
Node<TYPE>*
find(Node<TYPE>* tree,
	 const TYPE& key)
{
	while (tree) {
		if (key == tree->d_) return tree;
		size_t i = (size_t)(key > tree->d_);
		tree = tree->c_[i];
	}

	return 0;
}

/**
 * 二分探索木の各値を表示 (preorder)
 * @param[in]	node	二分探索木
 */
template<typename TYPE>
void
print_preorder(const Node<TYPE>* node)
{
	if (!node) return;

	std::printf(" %G", (double)node->d_);
	print_preorder<TYPE>(node->c_[0]);
	print_preorder<TYPE>(node->c_[1]);
}

/**
 * 二分探索木の各値を表示 (inorder)
 * @param[in]	node	二分探索木
 */
template<typename TYPE>
void
print_inorder(const Node<TYPE>* node)
{
	if (!node) return;

	print_inorder<TYPE>(node->c_[0]);
	std::printf(" %G", (double)node->d_);
	print_inorder<TYPE>(node->c_[1]);
}

/**
 * 二分探索木の各値を表示
 * @param[in]	node	二分探索木
 */
template<typename TYPE>
void
print(const Node<TYPE>* node)
{
	print_inorder<TYPE>(node);
	std::printf("\n");

	print_preorder<TYPE>(node);
	std::printf("\n");
}

/**
 * 二分探索木の全てのノードを削除
 * @param[in,out]	node	二分探索木
 */
template<typename TYPE>
void
all_delete(Node<TYPE>* node)
{
	if (!node) return;

	all_delete<TYPE>(node->c_[0]);
	all_delete<TYPE>(node->c_[1]);
	delete node;
}

/**
 * サンプル・コマンド
 */
int
main()
{
	int a1[] = {8, 2, 3, 7, 22, 1};
	int a2[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int a3[] = {3, 7};
	size_t l1 = sizeof(a1) / sizeof(a1[0]);
	size_t l2 = sizeof(a2) / sizeof(a2[0]);
	size_t l3 = sizeof(a3) / sizeof(a3[0]);

	Node<int>* tree(0);

	for (size_t i(0); i < l1; ++i) {
		tree = insert(tree, a1[i]);
	}

	for (size_t i(0); i < l2; ++i) {
		std::printf("%s\n", find(tree, a2[i]) ? "yes" : "no");
	}

	print(tree);

	for (size_t i(0); i < l3; ++i) {
		tree = remove(tree, a3[i]);
	}

	print(tree);

	all_delete(tree);

	return 0;
}
