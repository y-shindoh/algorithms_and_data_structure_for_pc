/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_257.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.257の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  n個の行列の連鎖 M_1, M_2, ..., M_n が与えられたとき、
  スカラー乗算の回数が最小になるように
  積 M_1 M_2 M_3 ... M_n の計算順序を決定する問題を、
  連鎖行列積問題 (Matrix-Chain Multiplication problem) と言います。

  n個の行列について、行列 M_i の次元が与えられたとき、
  積 M_1 M_2 ... M_n の計算に必要なスカラー乗算の最小の回数を求める
  プログラムを作成してください。
 */

/*
  メモ:
  アルゴリズム自体はすぐに思いついたが、
  インデックスの表現など、実装でいくつかつまずいてしまった。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * 連鎖行列積問題の解の算出器
 * @param[in]	h	各行列の高さ
 * @param[in]	w	各行列の幅
 * @param[in,out]	t	DPテーブル
 * @param[in]	s	計算対象の最左行列のインデックス
 * @param[in]	e	計算対象の最右行列のインデックス+1
 * @return	スカラー乗算の最小回数
 * @note	DPテーブルの初期化を、サンプル・コマンドの要領で事前に実施すること。
 */
size_t
solver(const size_t* h,
	   const size_t* w,
	   size_t** t,
	   size_t s,
	   size_t e)
{
	assert(h);
	assert(w);
	assert(t);
	assert(t[s]);
	assert(s < e);

	if (~(size_t)0 == t[s][e-1]) {
		size_t v(~(size_t)0);

		for (size_t i(s+1); i < e; ++i) {
			v = std::min(v, solver(h, w, t, s, i) + solver(h, w, t, i, e) + h[s] * h[i] * w[e-1]);
		}

		t[s][e-1] = v;
	}

	return t[s][e-1];
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	const size_t h[N] = {30, 35, 15, 5, 10, 20};
	const size_t w[N] = {35, 15, 5, 10, 20, 25};
	size_t* t[N];

	for (int i(0); i < N; ++i) {
		t[i] = new size_t[N];
		std::fill(t[i], t[i] + N, ~(size_t)0);
		t[i][i] = 0;	// 最初からある行列
	}

	std::printf("%lu\n", solver(h, w, t, 0, N));

	std::for_each(t, t + N, [](size_t* p) { delete [] p; });

	return 0;
}
