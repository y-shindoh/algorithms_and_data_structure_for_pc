/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_054.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.54の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  挿入ソート (Insertion Sort) は、手持ちのトランプを並び替える時に使われる、
  自然で思いつきやすいアルゴリズムの1つです。
  片手に持ったトランプを左から小さい順に並べる場合、1枚ずつカードを取り出して、
  それをその時点ですでにソートされている並びの適切な位置に挿入していくことによって、
  カードを並び替えることができます。

  N個の要素を含む整列Aを昇順に並び替える挿入ソートのプログラムを作成してください。
  上の擬似コードに従い、アルゴリズムを実装してください。
  アルゴリズムの動作を確認するため、
  各計算ステップでの配列 (入力直後の並びと、挿入処理が終了した直後の並び) を
  出力してください。
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
 * インサーション・ソート
 * @param[in,out]	array	処理対象の配列
 * @param[in]	length	配列 @a array の長さ
 */
template<typename TYPE>
void
insertion_sort(TYPE* array,
			   size_t length)
{
	assert(array);

	print_array<TYPE>(array, length);

	for (size_t i(1); i < length; ++i) {
		for (size_t j(i); 0 < j; --j) {
			if (array[j-1] <= array[j]) break;
			std::swap(array[j-1], array[j]);
		}
		print_array<TYPE>(array, length);
	}
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	int array[N] = {5, 2, 4, 6, 1, 3};

	insertion_sort(array, N);

	return 0;
}
