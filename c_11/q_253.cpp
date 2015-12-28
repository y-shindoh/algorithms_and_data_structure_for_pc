/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_253.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.253の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  最長共通部分列問題 (Longest Common Subsequence problem: LCS) は、
  2つの与えられた列 X = {x_1, x_2, ..., x_m} と Y = {y_1, y_2, ..., y_n} の
  最長共通部分列を求める問題です。

  ある列ZがYとY両方の部分列であるとき、ZをXとYの共通部分列と言います。
  例えば、 X = {a, b, c, b, d, a, b}, Y = {b, d, c, a, b, a} とすると、
  列 {b, c, a} はXとYの共通部分列です。
  一方、列 {b, c, a} はXとYの最長共通部分列ではありません。
  なぜなら、その長さは3であり、長さ4の共通部分列 {b, c, b, a} が存在するからです。
  長さが5以上の共通部分列が存在しないので、
  列 {b, c, b, a} はXとYの最長共通部分列の1つです。
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * longest common subsequenceの算出
 * @param[in]	a1	文字列
 * @param[in]	a2	文字列
 * @param[in]	l	文字列 @a a2 の長さ
 * @return	longest common subsequenceの文字数
 */
template<typename TYPE>
size_t
lcs(const TYPE* a1,
	const TYPE* a2,
	size_t l)
{
	assert(a1);
	assert(a2);
	assert(0 < l);

	size_t* m[2];
	size_t r(0);

	for (size_t i(0); i < 2; ++i) {
		m[i] = new size_t[l];	// エラー・チェックは省略
	}

	for (size_t i(0); a1[i]; ++i) {
		size_t h = i % 2;
		size_t k = 1 - h;
		for (size_t j(0); j < l; ++j) {
			m[h][j] = 0;
			if (0 < i) m[h][j] = std::max(m[h][j], m[k][j]);
			if (0 < j) m[h][j] = std::max(m[h][j], m[h][j-1]);
			if (a1[i] == a2[j]) {
				if (0 < i && 0 < j) {
					m[h][j] = std::max(m[h][j], m[k][j-1] + 1);
				}
				else {
					m[h][j] = 1;
				}
			}
			r = std::max(r, m[h][j]);
		}
	}

	std::for_each(m, m + 2, [](size_t* p) { delete [] p; });

	return r;
}

#define	N	3

/**
 * サンプル・コマンド
 */
int
main()
{
	const char a1[N][16] = {"abcbdab",
							"abc",
							"abc"};
	const char a2[N][16] = {"bdcaba",
							"abc",
							"bc"};

	for (int i(0); i < N; ++i) {
		std::printf("%lu\n", lcs(a1[i], a2[i], std::strlen(a2[i])));
	}

	return 0;
}
