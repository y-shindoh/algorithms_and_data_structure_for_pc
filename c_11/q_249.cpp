/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_249.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.249の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  フィボナッチ数列の第n項目を出力するプログラムを作成してください。
  ここではフィボナッチ数列を以下の再帰的な式で定義します:

  fib(n) = 1 (n = 0 or 1)
  fib(n) = fib(n - 1) + fib(n - 2)
 */

/*
  メモ:
  書籍ではメモ化で対応しているが、ここではDPで対応する。
 */

#include <cstdio>

/**
 * フィボナッチ数列の第n項を算出
 * @param[in]	n	項の番号
 * @return	フィボナッチ数列の第n項
 */
template<typename TYPE>
TYPE
fibonacci(size_t n)
{
	if (n <= 1) return 1;

	TYPE a(1);
	TYPE b(1);
	TYPE c;

	for (size_t i(2); i <= n; ++i) {
		c = b + a;
		a = b;
		b = c;
	}

	return c;
}

#define	N	3

int
main()
{
	std::printf("%G\n", fibonacci<double>(N));

	return 0;
}
