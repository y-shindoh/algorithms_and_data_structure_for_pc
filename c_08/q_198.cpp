/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_198.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.198の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  以下に示すアルゴリズムで、
  与えられた二分木のすべての節点を体系的に訪問するプログラムを作成してください。

  1. 根節点、左部分木、右部分木の順で節点の番号を出力する。
     これを木の先行順巡回 (Preorder Tree Walk) と呼びます。
  2. 左部分木、根節点、右部分木の順で節点の番号を出力する。
     これを木の中間順巡回 (Inorder Tree Walk) と呼びます。
  3. 左部分木、右部分木、根節点の順で節点の番号を出力する。
     これを木の後行順巡回 (Postorder Tree Walk) と呼びます。

  与えられる二分木はn個の節点を持ち、
  それぞれ0からn-1の番号が割り当てられているものとします。
 */

#include <cstdio>
#include <cassert>
#include <vector>

#define	INVALID_ID_	(~(size_t)0)

/**
 * 二分木のノード
 */
class Node
{
public:

	size_t c_[2];	// 子ノードのID

	/**
	 * コンストラクタ
	 * @param[in]	left	左の子のID
	 * @param[in]	right	右の子のID
	 */
	Node(size_t left = INVALID_ID_,
		 size_t right = INVALID_ID_)
		{
			c_[0] = left;
			c_[1] = right;
		}
};

/**
 * preorderの巡回
 * @param[in]	nodes	ノード群
 * @param[in]	index	表示対象のノード
 */
void
preorder_tree_walk(const std::vector<Node*>& nodes,
				   size_t index)
{
	if (index == INVALID_ID_) return;

	assert(index < nodes.size());

	std::printf(" %lu", index);

	for (size_t i(0); i < 2; ++i) {
		preorder_tree_walk(nodes, nodes[index]->c_[i]);
	}
}

/**
 * inorderの巡回
 * @param[in]	nodes	ノード群
 * @param[in]	index	表示対象のノード
 */
void
inorder_tree_walk(const std::vector<Node*>& nodes,
				  size_t index)
{
	if (index == INVALID_ID_) return;

	assert(index < nodes.size());

	inorder_tree_walk(nodes, nodes[index]->c_[0]);

	std::printf(" %lu", index);

	inorder_tree_walk(nodes, nodes[index]->c_[1]);
}

/**
 * postorderの巡回
 * @param[in]	nodes	ノード群
 * @param[in]	index	表示対象のノード
 */
void
postorder_tree_walk(const std::vector<Node*>& nodes,
					size_t index)
{
	if (index == INVALID_ID_) return;

	assert(index < nodes.size());

	for (size_t i(0); i < 2; ++i) {
		postorder_tree_walk(nodes, nodes[index]->c_[i]);
	}

	std::printf(" %lu", index);
}

#define	N	9

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector<Node*> nodes;

	nodes.push_back(new Node(1, 4));
	nodes.push_back(new Node(2, 3));
	nodes.push_back(new Node);
	nodes.push_back(new Node);
	nodes.push_back(new Node(5, 8));
	nodes.push_back(new Node(6, 7));
	nodes.push_back(new Node);
	nodes.push_back(new Node);
	nodes.push_back(new Node);

	assert(nodes.size() == N);

	std::vector<bool> flags(nodes.size(), true);

	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		for (size_t i(0); i < 2; ++i) {
			if ((*it)->c_[i] == INVALID_ID_) continue;
			flags[(*it)->c_[i]] = false;
		}
	}

	for (size_t i(0); i < nodes.size(); ++i) {
		if (!flags[i]) continue;
		std::printf("Preorder\n");
		preorder_tree_walk(nodes, i);
		std::printf("\nInorder\n");
		inorder_tree_walk(nodes, i);
		std::printf("\nPostorder\n");
		postorder_tree_walk(nodes, i);
		std::printf("\n");
		break;	// ルートをたどり終えた
	}

	return 0;
}
