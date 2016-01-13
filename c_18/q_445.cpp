/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_445.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.445の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  2つの整数m, nについて、
  m^nを1,000,000,007で割った余りを求めてください。
 */

#include <cstdio>

/**
 * べき乗を算出
 * @param[in]	base	底
 * @param[in]	exponent	冪指数
 * @param[in]	divisor	算出値を余りにするときの除数
 * @return	べき乗の値
 */
template<typename TYPE>
TYPE
exponentiation(TYPE base,
			   TYPE exponent,
			   TYPE divisor = 0)
{
	TYPE r(1);

	for (size_t i(0); exponent; ++i) {
		if ((1 << i) & exponent) r *= base;
		base *= base;
		if (0 < divisor) {
			r %= divisor;
			base %= divisor;
		}
		exponent &= ~(1 << i);
	}

	return r;
}

/**
 * サンプル・コマンド
 */
int
main()
{
	std::printf("%lu\n", exponentiation<size_t>(5, 8, 1000000007));

	return 0;
}
