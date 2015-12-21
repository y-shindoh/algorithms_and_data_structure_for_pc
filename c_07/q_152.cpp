/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_152.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.152の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  マージソート (Merge Sort) は次の分割統治法に基づく高速なアルゴリズムです。

  n個の整数を含む数列Sを上の擬似コード (省略) に従ったマージソートで
  昇順に整列するプログラムを作成してください。
  また、merge における比較回数の総数を報告してください。
 */

#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * マージソート
 * @param[in,out]	data	入出力データ
 * @param	buffer	作業領域
 * @param[in]	n	配列 @a data の要素数
 * @note	配列 @a buffer は @a n より長いこと。
 */
template<typename TYPE>
void
merge_sort(TYPE* data,
		   TYPE* buffer,
		   size_t n)
{
	assert(data);
	assert(buffer);

	size_t m = n / 2;

	if (1 < m) merge_sort(data, buffer, m);
	if (1 < n - m) merge_sort(data + m, buffer, n - m);

	if (0 < m) std::memcpy((void*)buffer, (const void*)data, sizeof(TYPE) * m);

	size_t h(0);
	size_t k(m);

	for (size_t i(0); i < n; ++i) {
		if (m <= h) break;
		if (n <= k) {
			std::memcpy((void*)(data + i), (const void*)(buffer + h), sizeof(TYPE) * (m - h));
			break;
		}
		if (buffer[h] <= data[k]) {
			data[i] = buffer[h++];
		}
		else {
			data[i] = data[k++];
		}
	}
}

#define	N	10

/**
 * サンプル・コマンド
 */
int
main()
{
	int a[N] = {8, 5, 9, 2, 6, 3, 7, 1, 10, 4};
	int b[N];

	for (int i(0); i < N; ++i) {
		std::printf("%d ", a[i]);
	}
	std::printf("\n");

	merge_sort(a, b, N);

	for (int i(0); i < N; ++i) {
		std::printf("%d ", a[i]);
	}
	std::printf("\n");

	return 0;
}
