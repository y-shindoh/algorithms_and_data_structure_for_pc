/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_188.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.188の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた根付き木の各節点uについて、
  以下の情報を出力するプログラムを作成してください。

  - uの節点番号
  - uの節点の種類 (根、内部ノードまたは葉)
  - uの親の節点番号
  - uの子のリスト
  - uの深さ

  ここでは、与えられる木はn個の節点を持ち、
  それぞれ0からn-1の番号が割り当てられているものとします。
 */

/*
  メモ:
  出力の制限「節点の情報はその番号が小さい順に出力してください」から
  全ノードを外部の std::vector に格納する形で構築した。
 */

#include <cstdio>
#include <cassert>
#include <vector>

#define	INVALID_ID_	(~(size_t)0)

/**
 * 根付き木のノード
 * @note	全ノードが外部に std::vector で保持されている場合を想定。
 */
template<typename TYPE>
class Node
{
public:
	TYPE data_;		///< データ (実際には使っていない)
	size_t depth_;	///< ノードの深さ
	size_t parent_;	///< 親ノードのID
	std::vector<size_t> children_;	///< 子ノードのID

	/**
	 * コンストラクタ
	 * @param[in]	data	データ
	 */
	Node(const TYPE& data)
		: data_(data), depth_(0), parent_(INVALID_ID_)
		{
			;
		}

	/**
	 * ノードの状態を表示
	 * @param[in]	id	ノードのID
	 */
	void
	print(size_t id = INVALID_ID_)
		{
			if (id != INVALID_ID_) std::printf("node %lu: ", id);

			if (parent_ == INVALID_ID_) {
				std::printf("parent = -1, ");
			}
			else {
				std::printf("parent = %lu, ", parent_);
			}

			std::printf("depth = %lu, ", depth_);

			if (parent_ == INVALID_ID_) {
				std::printf("root, ");
			}
			else if (children_.empty()) {
				std::printf("leaf, ");
			}
			else {
				std::printf("internal node, ");
			}

			std::printf("[");
			for (size_t i(0); i < children_.size(); ++i) {
				if (0 < i) std::printf(", ");
				std::printf("%lu", children_[i]);
			}
			std::printf("]\n");
		}

	/**
	 * 各ノードに親ノードを設定
	 * @param[in,out]	nodes	ノード列
	 * @return	根ノードのID
	 */
	static size_t
	SetParent(std::vector<Node<TYPE>*>& nodes)
		{
			for (size_t i(0); i < nodes.size(); ++i) {
				if (!nodes[i]) continue;
				for (auto j = nodes[i]->children_.begin(); j != nodes[i]->children_.end(); ++j) {
					nodes[*j]->parent_ = i;
				}
			}

			for (size_t i(0); i < nodes.size(); ++i) {
				if (!nodes[i]) continue;
				if (nodes[i]->parent_ != INVALID_ID_) continue;
				return i;
			}

			return INVALID_ID_;
		}

	/**
	 * 各ノードに深さを設定
	 * @param[in,out]	nodes	ノード列
	 * @param[in]	index	処理対象のノードのID
	 * @param[in]	depth	処理対象のノードの深さ
	 * @note	外部からの呼び出し時には、@a index に @a SetParent の返り値を設定すること。
	 */
	static void
	SetDepth(std::vector<Node<TYPE>*>& nodes,
			 size_t index,
			 size_t depth = 0)
		{
			if (index == INVALID_ID_) return;

			assert(index < nodes.size());
			assert(nodes[index]);

			nodes[index]->depth_ = depth;
			for (size_t i(0); i < nodes[index]->children_.size(); ++i) {
				SetDepth(nodes, nodes[index]->children_[i], depth + 1);
			}
		}
};

#define	N	13

int
main()
{
	std::vector<Node<int>*> tree;

	tree.push_back(new Node<int>(0));	// dataは何でも良い
	tree.back()->children_.push_back(1);
	tree.back()->children_.push_back(4);
	tree.back()->children_.push_back(10);

	tree.push_back(new Node<int>(1));	// dataは何でも良い
	tree.back()->children_.push_back(2);
	tree.back()->children_.push_back(3);

	tree.push_back(new Node<int>(2));	// dataは何でも良い

	tree.push_back(new Node<int>(3));	// dataは何でも良い

	tree.push_back(new Node<int>(4));	// dataは何でも良い
	tree.back()->children_.push_back(5);
	tree.back()->children_.push_back(6);
	tree.back()->children_.push_back(7);

	tree.push_back(new Node<int>(5));	// dataは何でも良い

	tree.push_back(new Node<int>(6));	// dataは何でも良い

	tree.push_back(new Node<int>(7));	// dataは何でも良い
	tree.back()->children_.push_back(8);
	tree.back()->children_.push_back(9);

	tree.push_back(new Node<int>(8));	// dataは何でも良い

	tree.push_back(new Node<int>(9));	// dataは何でも良い

	tree.push_back(new Node<int>(10));	// dataは何でも良い
	tree.back()->children_.push_back(11);
	tree.back()->children_.push_back(12);

	tree.push_back(new Node<int>(11));	// dataは何でも良い

	tree.push_back(new Node<int>(12));	// dataは何でも良い

	size_t h = Node<int>::SetParent(tree);
	Node<int>::SetDepth(tree, h);

	assert(tree.size() == N);

	for (size_t i(0); i < tree.size(); ++i) {
		tree[i]->print(i);
		delete tree[i];
	}

	return 0;
}
