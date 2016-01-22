/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_324.2.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.324の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  いくつかの属性を持つレコードの集合 (データベース) から、
  特定の属性の値が指定された領域に入るものを見つける問題を領域探索と呼びます。

  2次元の平面上の点の集合に対し、
  与えられた領域に含まれる点を列挙してください。
  ただし、与えられた点の集合に対して、点の追加・削除は行われません。
 */

#include <cstdio>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

/**
 * kD木のノード
 */
class Node
{
public:

	size_t i_;		///< 外部データのインデックス
	Node* c_[2];	///< 子ノード (注目する要素に関する二分探索木)

	/**
	 * コンストラクタ
	 * @param[in]	i	外部データのインデックス
	 */
	Node(size_t i)
		: i_(i)
		{
			c_[0] = c_[1] = 0;
		}

	/**
	 * デストラクタ
	 */
	~Node()
		{
			for (size_t i(0); i < 2; ++i) {
				if (c_[i]) delete c_[i];
			}
		}
};

/**
 * 注目する要素によるインデックスをソーティング
 * @param[in,out]	buffer	インデックス
 * @param[in]	values	外部データ
 * @param[in]	lenght	配列 @a values の要素数
 * @param[in]	depth	注目する要素の深さ
 * @note	本当は選択アルゴリズムで実装すべきだが、
			ここではクイック・ソートで実装している。
 */
template<typename TYPE, size_t N>
void
sort_kdtree(size_t* buffer,
			const std::array<TYPE, N>* values,
			size_t length,
			size_t depth)
{
	assert(buffer);
	assert(values);

	if (length < 2) return;

	size_t k = length / 2;
	size_t j(1);
	depth %= N;

	std::swap(buffer[0], buffer[k]);

	for (size_t i(0); i < length; ++i) {
		if (values[buffer[0]][depth] <= values[buffer[i]][depth]) continue;
		std::swap(buffer[i], buffer[j]);
		++j;
	}

	std::swap(buffer[0], buffer[j-1]);

	if (1 < j - 1) sort_kdtree<TYPE, N>(buffer, values, j - 1, depth);
	if (1 + j < length) sort_kdtree<TYPE, N>(buffer + j, values, length - j, depth);
}

/**
 * kD木を構築
 * @param[in,out]	buffer	インデックス
 * @param[in]	values	外部データ
 * @param[in]	lenght	配列 @a values の要素数
 * @param[in]	depth	注目する要素の深さ
 * @return	kD木のノード
 */
template<typename TYPE, size_t N>
Node*
build_kdtree(size_t* buffer,
			 const std::array<TYPE, N>* values,
			 size_t length,
			 size_t depth = 0)
{
	assert(buffer);
	assert(values);

	if (length == 0) return 0;

	sort_kdtree<TYPE, N>(buffer, values, length, depth);

	size_t k = length / 2;
	Node* node = new Node(buffer[k]);

	node->c_[0] = build_kdtree<TYPE, N>(buffer, values, k, depth + 1);
	node->c_[1] = build_kdtree<TYPE, N>(buffer + k + 1, values, length - k - 1, depth + 1);

	return node;
}

/**
 * kD木から指定領域内の要素を探索
 * @param[in]	node	kD木のノード
 * @param[in]	values	外部データ
 * @param[out]	output	要素のインデックス
 * @param[in]	from	指定領域の始端
 * @param[in]	to	指定領域の末端
 * @param[in]	depth	注目する要素の深さ
 */
template<typename TYPE, size_t N>
void
find_kdtree(const Node* node,
			const std::array<TYPE, N>* values,
			std::vector<size_t>& output,
			const std::array<TYPE, N>& from,
			const std::array<TYPE, N>& to,
			size_t depth = 0)
{
	assert(node);
	assert(values);

	bool f(true);

	for (size_t i(0); i < N; ++i) {
		if (from[i] <= values[node->i_][i]) continue;
		f = false;
		break;
	}

	if (f) {
		for (size_t i(0); i < N; ++i) {
			if (values[node->i_][i] <= to[i]) continue;
			f = false;
			break;
		}
	}

	if (f) output.push_back(node->i_);

	depth %= N;
	if (node->c_[0] && values[node->i_][depth] <= to[depth]) {
		find_kdtree(node->c_[0], values, output, from, to, depth + 1);
	}
	if (node->c_[1] && from[depth] <= values[node->i_][depth]) {
		find_kdtree(node->c_[1], values, output, from, to, depth + 1);
	}
}

#define	M	6
#define	N	2

/**
 * サンプル・コマンド
 */
int
main()
{
	const std::array<int, 2> values[M] = {{{2, 1}},
										  {{2, 2}},
										  {{4, 2}},
										  {{6, 2}},
										  {{3, 3}},
										  {{5, 4}}};
	size_t buffer[M];
	for (size_t i(0); i < (size_t)M; ++i) buffer[i] = i;

	Node* kdt = build_kdtree<int, 2>(buffer, values, M);

	const std::array<int, 2> keys[N][2] = {{{{2, 0}},
											{{4, 4}}},
										   {{{4, 2}},
											{{10, 5}}}};
	std::vector<size_t> output;

	for (size_t i(0); i < (size_t)N; ++i) {
		find_kdtree<int, 2>(kdt, values, output, keys[i][0], keys[i][1]);
		for (auto j : output) std::printf("%lu\n", j);
		std::printf("\n");
		output.clear();
	}

	delete kdt;

	return 0;
}
