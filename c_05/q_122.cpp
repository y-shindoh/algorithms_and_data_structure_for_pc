/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_122.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.122の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  n個の整数を含む整数Sと、q個の異なる整数を含む整数Tを読み込み、
  Tに含まれる整数の中でSに含まれるものの個数Cを出力するプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

namespace ys
{
	/**
	 * std::lower_bound の代替
	 */
	template<typename TYPE>
	const TYPE*
	lower_bound(const TYPE* a,
				const TYPE* b,
				const TYPE& k)
	{
		assert(a);
		assert(b);
		assert(0 < b - a);

		int s(0);			// k以下の末尾 or 配列 a の先頭
		int e((int)(b-a));	// k超の先頭
		int i;

		while (s + 1 < e) {
			i = (s + e) / 2;
			if (a[i] <= k) s = i;
			else e = i;
		}

		if (a[s] != k) return b;

		return a + s;
	}

	/**
	 * st::upper_bound の代替
	 */
	template<typename TYPE>
	const TYPE*
	upper_bound(const TYPE* a,
				const TYPE* b,
				const TYPE& k)
	{
		assert(a);
		assert(b);
		assert(0 < b - a);

		int s(0);			// k以下の末尾 or 配列 a の先頭
		int e((int)(b-a));	// k超の先頭
		int i;

		while (s + 1 < e) {
			i = (s + e) / 2;
			if (a[i] <= k) s = i;
			else e = i;
		}

		return a + e;
	}
};

/**
 * 問題の回答
 * @param[in]	n	配列 @a S の要素数
 * @param[in]	S	探索対象の配列
 * @param[in]	q	配列 @a C の要素数
 * @param[in]	T	探索元の配列
 * @return	一致した要素数
 */
template<typename TYPE>
size_t
count(size_t n,
	  const TYPE* S,
	  size_t q,
	  const TYPE* T)
{
	assert(S);
	assert(T);

	size_t r(0);
	const TYPE* it;

	for (size_t i(0); i < q; ++i) {
//		it = std::lower_bound(S, S + n, T[i]);
		it = ys::lower_bound(S, S + n, T[i]);
		if (it == S + n) continue;
//		r += std::upper_bound(S, S + n, T[i]) - it;
		r += ys::upper_bound(S, S + n, T[i]) - it;
	}

	return r;
}

#define	N	5
#define	Q	3

/**
 * サンプル・コマンド
 */
int
main()
{
	int S[N] = {1, 2, 3, 4, 5};
	int T[Q] = {3, 4, 1};

	std::printf("%lu\n", count(N, S, Q, T));

	return 0;
}
