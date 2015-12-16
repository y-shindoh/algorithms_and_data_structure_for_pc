/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_070.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.70の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  トランプのカードを整列しましょう。
  ここでは、4つの絵柄 (suit) S, H, C, Dと9つの数字 (value) 1, 2, ..., 9から構成される
  計36枚のカードを用います。
  例えばハートの8は "H8"、ダイヤの1は "D1" と表します。

  バブルソート及び選択ソートのアルゴリズムを用いて、
  与えられたN枚のカードをそれらの数字を基準に
  昇順に整列するプログラムを作成してください。
  アルゴリズムはそれぞれ以下に示す擬似コード (ここでは省略) に従うものとします。
  配列の要素は0オリジンで記述されています。

  また、各アルゴリズムについて、
  与えられた入力に対して安定な出力を行っているか報告してください。
  ここでは、同じ数字を持つカードが複数ある場合
  それらが入力に出現する順序で出力されることを、「安定な出力」と呼ぶことにします。
  (※常に安定な出力を行うソートをアルゴリズムを安定なソートアルゴリズムと言います。)
 */

#include <cstdio>
#include <cassert>
#include <utility>

/**
 * 配列を標準出力に出力
 * @param[in]	values_1	出力対象の配列
 * @param[in]	values_2	出力対象の配列
 * @param[in]	indexes	出力順のインデックスの配列
 * @param[in]	length	配列 @a array の長さ
 */
template<typename TYPE_1, typename TYPE_2>
void
print_array(const TYPE_1* values_1,
			const TYPE_2* values_2,
			const size_t* indexes,
			size_t length)
{
	assert(values_1);
	assert(values_2);
	assert(indexes);

	size_t j;

	for (size_t i(0); i < length; ++i) {
		if (0 < i) std::printf(" ");
		j = indexes[i];
		std::printf("%c%G", (char)values_1[j], (double)values_2[j]);
	}
	std::printf("\n");
}

/**
 * バブル・ソート
 * @param[in]	values	処理対象の配列
 * @param[in,out]	indexes	インデックスの配列
 * @param[in]	length	配列 @a values の長さ
 */
template<typename TYPE>
void
bubble_sort(const TYPE* values,
			size_t* indexes,
			size_t length)
{
	assert(values);
	assert(indexes);
	assert(length < ~(size_t)0);

	size_t h(~(size_t)0);	// 未ソート範囲
	size_t k(length);

	while (k < h) {
		h = k;
		for (size_t i(1); i < h; ++i) {
			if (values[indexes[i-1]] <= values[indexes[i]]) continue;
			std::swap(indexes[i-1], indexes[i]);
			k = i;
		}
	}
}

/**
 * セレクション・ソート
 * @param[in]	values	処理対象の配列
 * @param[in,out]	indexes	インデックスの配列
 * @param[in]	length	配列 @a values の要素数
 * @return	要素の交換回数
 */
template<typename TYPE>
void
selection_sort(const TYPE* values,
			   size_t* indexes,
			   size_t length)
{
	assert(values);
	assert(indexes);

	size_t h, k;

	for (size_t i(0); i < length; ++i) {
		h = length - i - 1;
		k = 0;
		for (size_t j(1); j <= h; ++j) {
			if (values[indexes[k]] >= values[indexes[j]]) continue;
			k = j;
		}
		if (k == h) continue;
		std::swap(indexes[k], indexes[h]);
	}
}

#define	N	5

/**
 * サンプル・コマンド
 */
int
main()
{
	int numbers[N] = {4, 9, 4, 2, 3};	// 数字
	char suits[N] = {'H', 'C', 'S', 'D', 'C'};	// 絵柄
	size_t indexes_1[N];
	size_t indexes_2[N];
	bool stable(true);

	for (int i(0); i < N; ++i) indexes_1[i] = indexes_2[i] = i;

	// バブル・ソート
	bubble_sort(numbers, indexes_1, N);
	print_array(suits, numbers, indexes_1, N);
	std::printf("Stable\n");	// 安定ソートと仮定 (手抜き)

	// 選択ソート
	selection_sort(numbers, indexes_2, N);
	print_array(suits, numbers, indexes_2, N);
	for (int i(0); i < N; ++i) {
		if (indexes_1[i] == indexes_2[i]) continue;
		stable = false;
		break;
	}
	std::printf("%s\n", stable ? "Stable" : "Not stable");

	return 0;
}
