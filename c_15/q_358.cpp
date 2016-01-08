/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_358.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.358の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた重み付きグラフ G = (V, E) に対する
  最小全域木の辺の重みの総和を計算するプログラムを作成してください。
 */

/*
  メモ:
  union find treeの実装はp.318のものを流用した。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>

/**
 * union find tree
 */
template<typename TYPE>
class UnionFindTree
{
private:

	std::vector<TYPE> parent_;	///< 集合の代表元 or それに準じる元
	std::vector<TYPE> rank_;	///< 集合の木表現における深さ

	/**
	 * 代表元の取得
	 * @param[in]	i	集合の元
	 * @return	集合の代表元
	 */
	TYPE
	find(const TYPE& i)
		{
			assert(i < parent_.size());

			if (parent_[i] != i) parent_[i] = find(parent_[i]);

			return parent_[i];
		}

public:

	/**
	 * コンストラクタ
	 * @param[in]	n	初期の集合の総数
	 */
	UnionFindTree(const TYPE& n)
		: parent_(n), rank_(n, 1)
		{
			for (TYPE i(0); i < n; ++i) {
				parent_[i] = i;
			}
		}

	/**
	 * 集合の統合
	 * @param[in]	i	集合の元
	 * @param[in]	j	集合の元
	 */
	void
	unite(TYPE i,
		  TYPE j)
		{
			assert(i < parent_.size());
			assert(j < parent_.size());

			i = find(i);
			j = find(j);

			if (rank_[i] < rank_[j]) std::swap(i, j);
			if (rank_[i] == rank_[j]) rank_[i]++;

			parent_[j] = i;
		}

	/**
	 * 2つの元が同一集合の属するか確認
	 * @param[in]	i	集合の元
	 * @param[in]	j	集合の元
	 * @return	true: 属する, false: 属さない
	 */
	bool
	same(const TYPE& i,
		 const TYPE& j)
		{
			assert(i < parent_.size());
			assert(j < parent_.size());

			return find(i) == find(j);
		}
};

typedef	std::tuple<size_t, size_t, size_t>	CVV;	// 重み, 頂点, 頂点

/**
 * 最小全域木の総コストの算出
 * @param[in]	cvv	辺のリスト
 * @param[in]	n	頂点数
 * @return	最小全域木の総コスト
 */
size_t
calculate(std::vector<CVV>& cvv,
		  size_t n)
{
	UnionFindTree<size_t> uft(n);
	size_t r(0);

	std::sort(cvv.begin(), cvv.end());

	for (auto v : cvv) {
		assert(std::get<1>(v) < n);
		assert(std::get<2>(v) < n);
		if (uft.same(std::get<1>(v), std::get<2>(v))) continue;
		uft.unite(std::get<1>(v), std::get<2>(v));
		r += std::get<0>(v);
	}

	return r;
}

#define	M	6
#define	N	9

/**
 * サンプル・コマンド
 */
int
main()
{
	const int vvc[N][3] = {{0, 1, 1},
						   {0, 2, 3},
						   {1, 2, 1},
						   {1, 3, 7},
						   {2, 4, 1},
						   {1, 4, 3},
						   {3, 4, 1},
						   {3, 5, 1},
						   {4, 5, 6}};
	std::vector<CVV> cvv;

	for (auto v : vvc) {
		assert(v[0] < M);
		assert(v[1] < M);
		cvv.push_back(CVV(v[2], v[0], v[1]));
	}

	std::printf("%lu\n", calculate(cvv, M));

	return 0;
}
