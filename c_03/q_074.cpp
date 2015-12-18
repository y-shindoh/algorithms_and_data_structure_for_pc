/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_074.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.74の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  次のプログラム (ここでは省略) は、
  挿入ソートを応用してn個の整数を含む数列Aを昇順に整列するプログラムです。

  shellSort(A, n) は、
  一定の間隔gだけ離れた要素のみを対象とした挿入ソートである insertionSort(A, n, g) を、
  最初は大きい値からgを狭めながら繰り返します。
  これをシェル・ソートと言います。

  上の擬似コード (ここでは省略) の?を埋めてこのプログラムを完成させてください。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <utility>

/**
 * 配列を標準出力に出力
 * @param[in]	array	出力対象の配列
 * @param[in]	length	配列 @a array の長さ
 */
template<typename TYPE>
void
print_array(const TYPE* array,
			size_t length)
{
	assert(array);

	for (size_t i(0); i < length; ++i) {
		if (0 < i) std::printf(" ");
		std::printf("%G", (double)array[i]);
	}
	std::printf("\n");
}

/**
 * インサーション・ソート
 * @param[in,out]	array	処理対象の配列
 * @param[in]	length	配列 @a array の長さ
 * @param[in]	gap	比較する要素間の距離
 * @return	要素の交換回数
 */
template<typename TYPE>
size_t
insertion_sort(TYPE* array,
			   size_t length,
			   size_t gap = 1)
{
	assert(array);
	assert(0 < gap);

	size_t r(0);	// 要素の交換回数

	for (size_t i(gap); i < length; ++i) {
		for (size_t j(i); gap - 1 < j; j -= gap) {
			if (array[j-gap] <= array[j]) break;
			std::swap(array[j-gap], array[j]);
			++r;
		}
	}

	return r;
}

/**
 * シェル・ソート
 * @param[in,out]	array	処理対象の配列
 * @param[out]	gaps	ソート処理の間隔の配列 (末端は0)
 * @param[in]	length	配列 @a array の長さ
 * @return	要素の交換回数
 */
template<typename TYPE>
size_t
shell_sort(TYPE* array,
		   size_t* gaps,
		   size_t length)
{
	assert(array);
	assert(gaps);
	assert(0 < length);

	if (length <= 1) return 0;

	// 間隔の算出
	size_t n(length);
	gaps[0] = 1;
	std::fill(gaps + 1, gaps + length, 0);
	for (size_t i(1); i < length; ++i) {
		gaps[i] = 3 * gaps[i-1] + 1;	// テキストの解説に従った
		if (gaps[i] < length) continue;
		n = i;
		gaps[i] = 0;
		break;
	}

	// ソート
	size_t r(0);
	size_t j;
	for (size_t i(0); i < n; ++i) {
		j = n - i - 1;
		if (gaps[j] == 0) continue;
		r += insertion_sort(array, length, gaps[j]);
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
	int array[N] = {5, 1, 4, 3, 2};
	size_t gaps[N];

	// 表示内容は設問と異なるものにした
	print_array(array, N);
	size_t r = shell_sort(array, gaps, N);
	print_array(array, N);
	std::printf("%lu\n", r);

	return 0;
}
