/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_441.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.441の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  2つの自然数x, yを入力とし、
  それらの最大公約数を求めるプログラムを作成してください。

  2つの整数xとyについて、
  x÷d と y÷d の余りがともに0になるdのうち最大のものを、
  xとyの最大公約数 (Greatest Common Divisor) と言います。
  例えば、35と14の最大公約数 gcd(35, 14) は7となります。
  これは、
  35の約数 {1, 5, 7, 35}、14の約数 {1, 2, 7, 14} の
  公約数 {1, 7} の最大値となります。
 */

#include <cstdio>
#include <utility>

/**
 * ユークリッドの互除法による最大公約数の算出器
 * @param[in]	a	処理対象
 * @param[in]	b	処理対象
 * @return	最大公約数
 */
template<typename TYPE>
TYPE
gcd(TYPE a,
	TYPE b)
{
	if (a < b) std::swap(a, b);

	while (0 < b) {
		a %= b;
		std::swap(a, b);
	}

	return a;
}

/**
 * サンプル・コマンド
 */
int
main()
{
	std::printf("%lu\n", gcd<size_t>(147, 105));

	return 0;
}
