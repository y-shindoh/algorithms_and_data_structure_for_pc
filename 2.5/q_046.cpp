/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_046.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.46の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  FX取引では、異なる国の通貨を交換することで為替差の利益を得ることができます。
  例えば、1ドル100円の時に1,000ドル買い、価格変動により1ドル108円になった時に売ると、
  (108円 - 100円) * 1,000ドル = 8,000円の利益を得ることができます。

  ある通貨について、
  時刻tにおける価格R_t (t = 0, 1, ..., n-1) が入力として与えられるので、
  価格の差 R_j - R_i (ただし、j > i とする) の最大値を求めてください。
 */

#include <cstdio>
#include <climits>
#include <cassert>
#include <algorithm>

/**
 * 回答のメソッド
 * @param[in]	input	価格列
 * @param[in]	length	配列 @a input の要素数
 * @return	価格差の最大値
 */
int
find_max_width(const int* input,
			   int length)
{
	assert(input);
	assert(1 < length);

	int min(input[0]);	// 過去の最小価格
	int width(INT_MIN);	// 価格差の最大値

	for (int i(1); i < length; ++i) {
		width = std::max(width, input[i] - min);
		min = std::min(min, input[i]);
	}

	return width;
}

#define	N	6
//#define	N	3

/**
 * サンプル・コマンド
 */
int
main()
{
	int a[N] = {5, 3, 1, 3, 4, 3};
//	int a[N] = {4, 3, 2};

	std::printf("%d\n", find_max_width(a, N));

	return 0;
}
