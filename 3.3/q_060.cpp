/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_060.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.60の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  バブルソートはその名前が表すように、
  泡 (Bubble) が水面に上がっていくように配列の要素が動いていきます。
  バブルソートは次のようなアルゴリズムで数列を昇順に並び替えます。

  数列Aを読み込み、バブルソートで昇順に並び替え出力するプログラムを作成してください。
  また、バブルソートで行われた要素の交換数も報告してください。
 */

#include <cstdio>
#include <cassert>
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
 * バブル・ソート
 * @param[in,out]	array	処理対象の配列
 * @param[in]	length	配列 @a array の長さ
 * @return	要素の交換回数
 */
template<typename TYPE>
size_t
bubble_sort(TYPE* array,
			size_t length)
{
	assert(array);
	assert(length < ~(size_t)0);

	size_t r(0);			// 交換回数
	size_t h(~(size_t)0);	// 未ソート範囲
	size_t k(length);

	while (k < h) {
		h = k;
		for (size_t i(1); i < h; ++i) {
			if (array[i-1] <= array[i]) continue;
			std::swap(array[i-1], array[i]);
			k = i;
			++r;
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
	int array[N] = {5, 3, 2, 4, 1};

	size_t k = bubble_sort(array, N);

	print_array(array, N);
	std::printf("%lu\n", k);

	return 0;
}
