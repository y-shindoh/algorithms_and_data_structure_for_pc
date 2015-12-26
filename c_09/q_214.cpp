/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_214.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.214の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  A: Binary Search Tree I (q_209.cppに該当) に、find 命令を追加し、
  二分探索木Tに対し、以下の命令を実行するプログラムを作成してください。

  - insert k: Tにキーkを挿入する
  - find k: Tにキーkが存在するか否かを報告する。
  - print: キーを木の中間順巡回と先行順巡回アルゴリズムで出力する。
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
	int a1[] = {30, 88, 12, 1, 20};
	int a2[] = {17, 25};
	size_t l1 = sizeof(a1) / sizeof(a1[0]);
	size_t l2 = sizeof(a2) / sizeof(a2[0]);

	Node<int>* tree(0);

	for (size_t i(0); i < l1; ++i) {
		tree = insert(tree, a1[i]);
	}

	std::printf("%s\n", find(tree, 12) ? "yes" : "no");

	for (size_t i(0); i < l2; ++i) {
		tree = insert(tree, a2[i]);
	}

	std::printf("%s\n", find(tree, 16) ? "yes" : "no");

	print(tree);

	all_delete(tree);

	return 0;
}
