/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_168.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.168の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  計数ソートは各要素が0以上k以下である要素数nの配列に対して
  線形時間 (O(n + k)) で動く安定なソーティングアルゴリズムです。

  入力数列 A の各要素 A_j について、
  A_j 以下の要素の数をカウンタ配列 C に記録し、
  その値を基に出力配列 B における A_j の位置を求めます。
  同じ数の要素が複数ある場合を考慮して、
  要素 A_j を出力 (Bに入れる) した後にカウンタ C[A_j] は修正します。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * 計数ソート
 * @param[in]	input	処理対象のデータ
 * @param[out]	output	処理結果のデータ
 * @param[in]	n	配列 @a input の要素数
 * @param	buffer	作業領域
 * @param[in]	m	配列 @a buffer の長さ (配列 @a data の最大値+2)
 * @note	安定性を放棄すれば、インプレース・ソートにできる。
 */
template<typename TYPE>
void
counting_sort(const TYPE* input,
			  TYPE* output,
			  size_t n,
			  size_t* buffer,
			  size_t m)
{
	assert(input);
	assert(output);
	assert(buffer);
	assert(2 <= m);

	std::fill(buffer, buffer + m, (size_t)0);

	for (size_t i(0); i < n; ++i) {
		assert(input[i] < (TYPE)(m - 1));
		buffer[input[i]+1]++;
	}

	for (size_t i(2); i < m - 1; ++i) {
		buffer[i] += buffer[i-1];
	}
	// 注意: buffer[m-1] は使わない。

	for (size_t i(0); i < n; ++i) {
		output[buffer[input[i]]] = input[i];
		buffer[input[i]]++;
	}
}

#define	N	7
#define	K	10000

/**
 * サンプル・コマンド
 */
int
main()
{
	unsigned int input[N] = {2, 5, 1, 3, 2, 3, 0};
	unsigned int output[N];
	size_t buffer[K+2];

	counting_sort(input, output, N, buffer, K+2);
#ifndef	_NDEBUG
	std::sort(input, input + N);	// 比較用
#endif	// !_NDEBUG

	for (int i(0); i < N; ++i) {
		assert(input[i] == output[i]);
		std::printf("%u ", output[i]);
	}
	std::printf("\n");

	return 0;
}
