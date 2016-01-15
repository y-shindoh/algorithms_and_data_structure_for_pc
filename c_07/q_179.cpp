/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_179.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.179の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  重さ w_i (i = 0, 1, ..., n-1) のn個の荷物が1列に並んでいます。
  これらの荷物をロボットアームを用いて並べ替えます。
  1度の操作でロボットアームは荷物iと荷物jを持ち上げ、
  それらの位置を交換することができますが、w_i + w_j のコストがかかります。
  ロボットアームは何度でも操作することができます。

  与えられた荷物の列を重さの昇順に整列するコストの最小値を求めてください。
 */

/*
  メモ:
  全く歯が立たず、書籍の説明でやっと理解できた。
 */

#include <cstdio>
#include <climits>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <algorithm>

/**
 * ソーティングのコスト最小値を算出
 * @param[in]	array	ソーティング対象
 * @param[in]	length	配列 @a array の要素数
 * @return	コストの最小値
 */
template<typename TYPE>
TYPE
min_cost_sort(const TYPE* array,
			  size_t length)
{
	assert(array);

	TYPE min = *std::min_element(array, array + length);
	TYPE max = *std::max_element(array, array + length);
	TYPE r(0);

	std::vector<TYPE> data(length);
	std::unordered_map<TYPE, size_t> correction;
	std::vector<bool> flags(length, false);

	// 各値の移動先を算出
	for (size_t i(0); i < length; ++i) data[i] = array[i];
	std::sort(data.begin(), data.end());
	for (size_t i(0); i < length; ++i) correction[data[i]] = i;
	data.clear();

	// グループ毎に探索
	for (size_t i(0); i < length; ++i) {
		if (flags[i]) continue;

		size_t c(i);
		TYPE sum(0);
		TYPE m(max);
		TYPE n(0);

		while (!flags[c]) {
			flags[c] = true;
			++n;
			TYPE v = array[c];
			m = std::min(m, v);
			sum += v;
			c = correction[v];
		}

		// 各グループのコストを加算
		r += std::min(sum + n * m - 2 * m, sum + m + (n + 1) * min);
	}

	return r;
}

#define	N	5

/**
 * サンプル・コマンド
 */
int
main()
{
	unsigned int array[N] = {1, 5, 3, 4, 2};

	std::printf("%u\n", min_cost_sort(array, N));

	return 0;
}
