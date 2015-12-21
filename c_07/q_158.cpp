/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_158.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.158の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  partition(A, p, r) は、配列 A[p..r] を A[p..q-1] の各要素が A[q] 以下で、
  A[q+1..r] の各要素が A[q] より大きい A[p..q-1] と A[q+1..r] に分割し、
  インデックスqを戻り値として返します。

  数列Aを読み込み、
  次の擬似コードに基づいた partition を行うプログラムを作成してください。

  ここで、rは配列Aの最後の要素を指す添字で、
  A[r] を基準として配列を分割することに注意してください。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * 末尾の要素を基準にパーティショニング
 * @param[in,out]	A	処理対象の配列
 * @param[in]	p	処理対象の最初の要素
 * @param[in]	r	処理対象の最後の要素
 * @return	処理後の基準の要素
 */
template<typename TYPE>
size_t
paritioan(TYPE* A,
		  size_t p,
		  size_t r)
{
	assert(A);
	assert(p <= r);

	if (p == r) return p;

	size_t q(p);

	for (size_t i(p); i < r; ++i) {
		if (A[i] > A[r]) continue;
		std::swap(A[i], A[q++]);
	}

	std::swap(A[r], A[q]);

	return q;
}

#define	N	12

/**
 * サンプル・コマンド
 */
int
main()
{
	int A[N] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};

	size_t j = paritioan(A, 0, N-1);

	for (size_t i(0); i < N; ++i) {
		if (i == j) {
			std::printf("[%d] ", A[i]);
		}
		else {
			std::printf("%d ", A[i]);
		}
	}
	std::printf("\n");

	return 0;
}
