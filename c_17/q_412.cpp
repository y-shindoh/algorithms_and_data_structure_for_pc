/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_412.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.412の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  額面が c_1, c_2, ..., c_m 円のm種類のコインを使って、
  n円を支払うときの、コインの最小の枚数を求めてください。
  各額面のコインは何度でも使用することができます。
 */

#include <cstdio>
#include <vector>

/**
 * コインの枚数を算出
 * @param[in]	coins	コインの種類
 * @param[in]	total	求める総額
 * @return	コインの枚数
 */
size_t
calculate(const std::vector<size_t>& coins,
		  size_t total)
{
	std::vector<size_t> work(total + 1, ~(size_t)0);
	work[0] = 0;

	for (size_t c : coins) {
		for (size_t i(0); i < total; ++i) {
			if (work[i] == ~(size_t)0) continue;
			if (total < i + c) continue;
			work[i+c] = std::min(work[i+c], work[i] + 1);
		}
	}

	return work[total];
}

#define	M	6
#define	N	15

/**
 * サンプル・コマンド
 */
int
main()
{
	const std::vector<size_t> coins = {{1, 2, 7, 8, 12, 50}};

	std::printf("%lu\n", calculate(coins, N));

	return 0;
}
