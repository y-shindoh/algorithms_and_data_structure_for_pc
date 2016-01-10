/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_421.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.421の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  数列 A = a_0, a_1, ..., a_n-1 の
  最長増加部分列 (LIS: Longest Increasing Subsequence) の長さを求めてください。
  数列Aの増加部分列は 0 <= i_0 < i_1 < ... < i_k < n かつ
  a_i0 < a_i1 < ... < a_ik を満たす部分列 a_i0, a_i1, ..., a_ik です。
  最長増加部分列はその中で最もkが大きいものです。
 */

#include <cstdio>
#include <array>
#include <vector>
#include <algorithm>

/**
 * 最長増加部部分列の算出
 * @param[in]	array	探索対象の配列
 * @param[in]	length	配列 @a array の要素数
 * @param[in]	max	配列 @a array 中のどの要素より大きな値
 * @return	最長増加部部分列の長さ
 */
template<typename TYPE>
size_t
search(const TYPE* array,
	   size_t length,
	   TYPE max = ~(TYPE)0)
{
	std::vector<TYPE> work(length + 1, max);

	for (size_t i(0); i < length; ++i) {
		auto it = std::lower_bound(work.begin(), work.end(), array[i]);
		*it = array[i];
	}

	return std::lower_bound(work.begin(), work.end(), max) - work.begin();
}

#define	N	5

/**
 * サンプル・コマンド
 */
int
main()
{
	std::array<size_t, N> array = {{5, 1, 3, 2, 4}};

	std::printf("%lu\n", search(&array[0], N));

	return 0;
}
