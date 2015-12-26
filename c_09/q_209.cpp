/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_209.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.209の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  二分探索木Tに新たに値Vを挿入するには、
  以下の擬似コードに示す (省略) insert を実行します。
  insert は、キーがv、左の子がNIL、右の子がNILであるような点zを受け取り、
  Tの正しい位置に挿入します。

  二分探索木Tに対し、以下の命令を実行するプログラムを作成してください。

  - insert k: Tにキーkを挿入する
  - print: キーを木の中間順巡回と先行順巡回アルゴリズムで出力する。

  挿入は上記擬似コード (省略) のアルゴリズムに従ってください。
 */

/*
  メモ:
  効率の都合から、メソッド insert の実装を書籍とは違うものとした。
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
	int a[] = {30, 88, 12, 1, 20, 17, 25};
	size_t l = sizeof(a) / sizeof(a[0]);

	Node<int>* tree(0);

	for (size_t i(0); i < l; ++i) {
		tree = insert(tree, a[i]);
	}

	print(tree);

	all_delete(tree);

	return 0;
}
