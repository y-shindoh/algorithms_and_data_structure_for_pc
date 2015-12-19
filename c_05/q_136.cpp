/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_136.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.136の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  重さがそれぞれ w_i (i = 0, 1, ..., n-1) のn個の荷物が、
  ベルトコンベアから順番に流れてきます。
  これらの荷物をk台のトラックに積みます。
  各トラックには連続する0個以上の荷物を積むことができますが、
  それらの重さの和がトラックの最大積載量Pを超えてはなりません。
  最大積載量Pはすべてのトラックで共通です。

  n, k, w_i が与えられるので、
  すべての荷物を積むために必要な
  最大積載量Pの最小値を求めるプログラムを作成してください。
 */

/*
  メモ:
  書籍では、トラックの台数ではなく、積んだ荷物の数で二分探索をしている。
 */

#include <cstdio>
#include <cassert>

/**
 * トラックの必要台数を算出
 * @param[in]	w	荷物の配列
 * @param[in]	n	配列 @a w の要素数
 * @param[in]	P	トラックの最大積載量
 * @return	トラックの必要台数
 * @note	トラックが何台あっても足りない場合は ~(size_t)0 が返却される。
 * @note	計算量は O(n)。
 */
template<typename TYPE>
size_t
count_trucks(const TYPE* w,
			 size_t n,
			 TYPE P)
{
	assert(w);

	TYPE p(0);
	size_t r(0);

	for (size_t i(0); i < n; ++i) {
		if (P < w[i]) return ~(size_t)0;
		if (p < w[i]) {
			p = P;
			++r;
		}
		p -= w[i];
	}

	return r;
}

/**
 * トラックの適切な最大積載量を算出
 * @param[in]	w	荷物の配列
 * @param[in]	n	配列 @a w の要素数
 * @param[in]	k	トラックの台数
 * @return	トラックの適切な最大積載量
 * @note	計算量は O(n log n)。
 */
template<typename TYPE>
TYPE
calculate_weight(const TYPE* w,
				 size_t n,
				 size_t k)
{
	assert(w);
	assert(k <= n);
	assert(0 < k);

	// 最大積載量の候補
	TYPE s(0);			// k超の末尾
	TYPE e(n*10000);	// k以下の先頭
	TYPE p;

	while (s + 1 < e) {
		p = (s + e) / 2;
		if (k < count_trucks(w, n, p)) {
			s = p;
		}
		else {
			e = p;
		}
	}

	return e;
}

#define	N	5
#define	K	3

/**
 * サンプル・コマンド
 */
int
main()
{
	size_t w[N] = {8, 1, 7, 3, 9};

	std::printf("%lu\n", calculate_weight(w, N, K));

	return 0;
}
