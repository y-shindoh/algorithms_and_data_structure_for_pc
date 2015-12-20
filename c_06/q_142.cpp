/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_142.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.142の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  長さnの数列Aと整数mに対して、
  Aの要素の中のいくつかの要素を足しあわせて
  mが作れるかどうかを判定するプログラムを作成してください。
  Aの各要素は1度だけ使うことができます。

  数列Aが与えられたうえで、質問としてq個の m_i が与えられるので、
  それぞれについて "yes" または "no" と出力してください。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * 問題の回答 (再帰版)
 * @param[in]	A	配列
 * @param[in]	n	配列 @a A の要素数
 * @param[in]	m	数値
 * @return	true: 配列の適切な要素の和が @a m と等しい, false: 全ての要素の和が等しくない
 * @note	最悪計算量は O(2^n)。
 */
template<typename TYPE>
bool
find_sum_1(const TYPE* A,
		   size_t n,
		   TYPE m)
{
	assert(A);

	if (n == 0) return m == 0;

	if (find_sum_1(A + 1, n - 1, m)) return true;
	if (find_sum_1(A + 1, n - 1, m - *A)) return true;

	return false;
}

/**
 * 問題の回答 (DP版)
 * @param[in]	A	配列
 * @param[in]	n	配列 @a A の要素数
 * @param[in]	m	数値
 * @param	dp	DPテーブル
 * @return	true: 配列の適切な要素の和が @a m と等しい, false: 全ての要素の和が等しくない
 * @note	最悪計算量は O(mn)。
 */
template<typename TYPE>
bool
find_sum_2(const TYPE* A,
		   size_t n,
		   TYPE m,
		   bool* dp)
{
	dp[0] = true;
	std::fill(dp + 1, dp + m + 1, false);

	for (size_t i(0); i < n; ++i) {
		for (size_t j(m); 0 < j; --j) {
			TYPE k = j - 1;
			if (!dp[k]) continue;
			if (m < k + A[i]) continue;
			if (k + A[i] == m) return true;
			dp[k + A[i]] = true;
		}
	}

	return false;
}

#define	N	5
#define	Q	4

/**
 * サンプル・コマンド
 */
int
main()
{
	int A[N] = {1, 5, 7, 10, 21};
	int m[Q] = {2, 4, 17, 8};
	bool dp[2000+1];

	for (size_t i(0); i < Q; ++i) {
//		std::printf("%s\n", find_sum_1(A, N, m[i]) ? "yes" : "no");
		std::printf("%s\n", find_sum_2(A, N, m[i], dp) ? "yes" : "no");
	}

	return 0;
}
