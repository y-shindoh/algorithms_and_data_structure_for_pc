/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_194.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.194の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた根付き二分木Tの各節点uについて、
  以下の情報を出力するプログラムを作成してください。

  - uの節点番号
  - uの親
  - uの兄弟
  - uの子の数
  - uの深さ
  - uの高さ
  - uの節点の種類 (根、内部ノードまたは葉)

  ここでは、与えられる木はn個の節点を持ち、
  それぞれ0からn-1の番号が割り当てられているものとします。
 */

/*
  メモ:
  q_188.cpp の実装を流用した関係で、
  全ノードを外部の std::vector に格納する形で構築した。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

#define	INVALID_ID_	(~(size_t)0)

/**
 * 根付き木のノード
 * @note	全ノードが外部に std::vector で保持されている場合を想定。
 */
template<typename TYPE>
class Node
{
public:
	TYPE data_;				///< データ (実際には使っていない)
	size_t depth_;			///< ノードの深さ
	size_t height_;			///< ノードの高さ
	size_t parent_;			///< 親ノードのID
	size_t sibling_;		///< 兄弟ノードのID
	size_t children_[2];	///< 子ノードのID

	/**
	 * コンストラクタ
	 * @param[in]	data	データ
	 */
	Node(const TYPE& data)
		: data_(data), depth_(0), height_(0),
		  parent_(INVALID_ID_), sibling_(INVALID_ID_)
		{
			children_[0] = children_[1] = INVALID_ID_;
		}

	/**
	 * 子ノードのIDを指定
	 * @param[in]	left	左の子のID
	 * @param[in]	right	右の子のID
	 */
	void
	set_children(size_t left,
				 size_t right)
		{
			children_[0] = left;
			children_[1] = right;
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

			if (sibling_ == INVALID_ID_) {
				std::printf("sibling = -1, ");
			}
			else {
				std::printf("sibling = %lu, ", sibling_);
			}

			size_t n(0);
			for (size_t i(0); i < 2; ++i ) {
				n += children_[i] != INVALID_ID_;
			}

			std::printf("degree = %lu, ", n);

			std::printf("depth = %lu, ", depth_);

			std::printf("height = %lu, ", height_);

			if (parent_ == INVALID_ID_) {
				std::printf("root\n");
			}
			else if (n == 0) {
				std::printf("leaf\n");
			}
			else {
				std::printf("internal node\n");
			}
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
				for (size_t j(0); j < 2; ++j) {
					size_t h = nodes[i]->children_[j];
					size_t k = nodes[i]->children_[1-j];
					if (h == INVALID_ID_) continue;
					nodes[h]->parent_ = i;
					nodes[h]->sibling_ = k;
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
	 * 各ノードに深さ・高さを設定
	 * @param[in,out]	nodes	ノード列
	 * @param[in]	index	処理対象のノードのID
	 * @param[in]	depth	処理対象のノードの深さ
	 * @return	最も深い子孫の深さ
	 * @note	外部からの呼び出し時には、@a index に @a SetParent の返り値を設定すること。
	 */
	static size_t
	SetDepth(std::vector<Node<TYPE>*>& nodes,
			 size_t index,
			 size_t depth = 0)
		{
			if (index == INVALID_ID_) return 0;

			assert(index < nodes.size());
			assert(nodes[index]);

			size_t h(depth);
			size_t k;

			nodes[index]->depth_ = depth;
			for (size_t i(0); i < 2; ++i) {
				k = SetDepth(nodes, nodes[index]->children_[i], depth + 1);
				h = std::max(h, k);
			}
			nodes[index]->height_ = h - depth;

			return h;
		}
};

#define	N	9

int
main()
{
	std::vector<Node<int>*> tree;

	tree.push_back(new Node<int>(0));	// dataは何でも良い
	tree.back()->set_children(1, 4);

	tree.push_back(new Node<int>(1));	// dataは何でも良い
	tree.back()->set_children(2, 3);

	tree.push_back(new Node<int>(2));	// dataは何でも良い

	tree.push_back(new Node<int>(3));	// dataは何でも良い

	tree.push_back(new Node<int>(4));	// dataは何でも良い
	tree.back()->set_children(5, 8);

	tree.push_back(new Node<int>(5));	// dataは何でも良い
	tree.back()->set_children(6, 7);

	tree.push_back(new Node<int>(6));	// dataは何でも良い

	tree.push_back(new Node<int>(7));	// dataは何でも良い

	tree.push_back(new Node<int>(8));	// dataは何でも良い

	size_t h = Node<int>::SetParent(tree);
	Node<int>::SetDepth(tree, h);

	assert(tree.size() == N);

	for (size_t i(0); i < tree.size(); ++i) {
		tree[i]->print(i);
		delete tree[i];
	}

	return 0;
}
