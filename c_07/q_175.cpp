/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_175.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.175の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  数列 A = {a_0, a_1, ..., a_n-1} について、
  a_i > a_j かつ i < j である組 {i, j} の個数を反転数と言います。
  反転数は次のバブルソート (省略) の交換回数と等しくなります。

  数列 A が与えられるので、A の反転数を求めてください。
  上の擬似コードのアルゴリズム (省略) をそのまま実装すると
  Time Limit Exceeded になることに注意してください。
 */

/*
  メモ:
  最初、ソート前後の位置の比較をすることを考えて失敗した。
  マージ・ソートを応用するヒントを知って対処できた。
 */

#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * マージ・ソート
 * @param[in,out]	data	処理対象の配列
 * @param	buffer	作業領域
 * @param[in]	n	配列 @a data の要素数
 * @return	反転数
 */
template<typename TYPE>
size_t
merge_sort(TYPE* data,
		   TYPE* bufer,
		   size_t n)
{
	assert(data);
	assert(bufer);

	if (n <= 1) return 0;

	size_t m = n / 2;
	size_t r(0);

	if (1 < m) r += merge_sort(data, bufer, m);
	if (1 < n - m) r += merge_sort(data + m, bufer, n - m);

	size_t h(0);
	size_t k(m);

	std::memcpy((void*)bufer, (const void*)data, sizeof(TYPE) * m);

	for (size_t i(0); i < n; ++i) {
		if (m <= h) break;
		if (n <= k) {
			std::memcpy((void*)(data + i), (const void*)(bufer + h), sizeof(TYPE) * (m - h));
			break;
		}
		if (bufer[h] <= data[k]) {
			data[i] = bufer[h++];
		}
		else {
			data[i] = data[k++];
			r += m - h;
		}
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
	int A[N] = {3, 5, 2, 1, 4};
	int b[N];

	std::printf("%lu\n", merge_sort(A, b, N));

	return 0;
}
