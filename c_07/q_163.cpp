/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_163.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.163の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  n枚のカードの列を整列します。
  各カードには1つの絵柄 (S, H, C, またはD) と1つの数のペアが書かれています。
  これらを以下の擬似コードに基づくクイックソートで
  昇順に整列するプログラムを作成してください。
  partition はALDS1_6_B (q_158.cppに相当) の擬似コードに基づくものとします。

  ここで、Aはカードが格納された配列であり、
  partition における比較演算は
  カードに書かれた「数」を基準に行われるものとします。

  また、与えられた入力に対して安定な出力を行っているかを報告してください。
  ここでは、同じ数を持つカードが複数ある場合、
  それらが入力で与えられた順序で現れる出力を「安定な出力」とします。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * バブル・ソート
 * @param[in,out]	indexes	カードのインデックスの配列
 * @param[in]	numbers	カードの数の配列
 * @param[in]	n	配列 @a indexes の長さ
 */
void
bubble_sort(size_t* indexes,
			const int* numbers,
			size_t n)
{
	assert(indexes);
	assert(numbers);

	size_t h(0);
	size_t k(n);

	while (h != k) {
		h = k;
		for (size_t i(1); i < h; ++i) {
			if (numbers[indexes[i-1]] <= numbers[indexes[i]]) continue;
			std::swap(indexes[i-1], indexes[i]);
			k = i;
		}
	}
}

/**
 * クイック・ソート
 * @param[in,out]	indexes	カードのインデックスの配列
 * @param[in]	numbers	カードの数の配列
 * @param[in]	n	配列 @a indexes の長さ
 */
void
quick_sort(size_t* indexes,
		   const int* numbers,
		   size_t n)
{
	assert(indexes);
	assert(numbers);

	if (n <= 1) return;

	size_t k(0);

	for (size_t i(0); i + 1 < n; ++i) {
		if (numbers[indexes[n-1]] < numbers[indexes[i]]) continue;
		std::swap(indexes[i], indexes[k++]);
	}

	std::swap(indexes[k], indexes[n-1]);

	if (1 < k) quick_sort(indexes, numbers, k);
	++k;
	if (k + 1 < n) quick_sort(indexes + k, numbers, n - k);
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	const char suits[N] = {'D', 'H', 'D', 'S', 'D', 'C'};
	const int numbers[N] = {3, 2, 1, 3, 2, 1};
	size_t indexes_1[N];
	size_t indexes_2[N];

	for (int i(0); i < N; ++i) {
		indexes_1[i] = indexes_2[i] = (size_t)i;
	}

	bubble_sort(indexes_1, numbers, N);
	quick_sort(indexes_2, numbers, N);

	bool flag(true);

	for (int i(0); i < N; ++i) {
		if (indexes_1[i] == indexes_2[i]) continue;
		flag = false;
		break;
	}

	std::printf("%s\n", flag ? "Stable" : "Not stable");
	for (size_t i(0); i < N; ++i) {
		std::printf("%c %d\n", suits[indexes_2[i]], numbers[indexes_2[i]]);
	}

	return 0;
}
