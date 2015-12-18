/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_065.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.65の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  選択ソートは、各計算ステップで1つの最小値を「選択」していく、
  直感的なアルゴリズムです。

  数列Aを読み込み、
  選択ソートのアルゴリズムで昇順に並び替え出力するプログラムを作成してください。
  上の擬似コード (ここでは省略) に従いアルゴルズムを実装してください。

  擬似コード7行目で、
  iとminjが異なり実際に交換が行われた回数も出力してください。
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
 * セレクション・ソート
 * @param[in,out]	array	処理対象の配列
 * @param[in]	length	配列 @a array の要素数
 * @return	要素の交換回数
 */
template<typename TYPE>
size_t
selection_sort(TYPE* array,
			   size_t length)
{
	assert(array);

	size_t r(0);	// 交換回数
	size_t h, k;

	for (size_t i(0); i < length; ++i) {
		h = length - i - 1;
		k = 0;
		for (size_t j(1); j <= h; ++j) {
			if (array[k] >= array[j]) continue;
			k = j;
		}
		if (k == h) continue;
		std::swap(array[k], array[h]);
		++r;
	}

	return r;
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	int array[N] = {5, 6, 4, 2, 1, 3};

	size_t k = selection_sort(array, N);

	print_array(array, N);
	std::printf("%lu\n", k);

	return 0;
}
