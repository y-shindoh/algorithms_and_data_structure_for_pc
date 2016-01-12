/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_436.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.436の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  約数が1とその数自身だけであるような自然数を素数と言います。
  例えば、最初の8つの素数は2, 3, 5, 7, 11, 13, 17, 19となります。
  1は素数ではありません。

  n個の整数を読み込み、
  それらに含まれる素数の数を出力するプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

/**
 * 数の中の素数をカウント
 * @param[in]	numbers	カウント対象の数
 * @return	素数の総数
 */
size_t
prime_numbers(const std::vector<size_t> numbers)
{
	auto it = std::max_element(numbers.begin(), numbers.end());
	std::vector<size_t> d;
	size_t r(0);

	if (2 <= *it) {
		d.push_back(2);

		for (size_t i(3); i * i < *it; i += 2) {
			bool f(false);
			for (size_t j : d) {
				if (i % j != 0) continue;
				f = true;
				break;
			}
			if (f) continue;
			d.push_back(i);
		}

		for (size_t i : numbers) {
			if (i < 2) continue;
			bool f(false);
			for (size_t j : d) {
				if (i < j * j) break;
				if (i % j != 0) continue;
				f = true;
				break;
			}
			if (f) continue;
			++r;
		}
	}

	return r;
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector<size_t> numbers = {{2, 3, 4, 5, 6, 7}};

	assert(numbers.size() == N);

	std::printf("%lu\n", prime_numbers(numbers));

	return 0;
}
