/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_416.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.416の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  価値が v_i 重さが w_i であるようなN個の商品と、容量がWのナップザックがあります。
  次の条件を満たすように、品物を選んでナップザックに入れます:
  - 選んだ品物の価値の合計をできるだけ高くする。
  - 選んだ品物の重さの総和はWを超えない。
 */

#include <cstdio>
#include <cassert>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>

/// 重さと価値
typedef	std::array<size_t, 2>	VW;

/**
 * ナップサック問題のソルバ
 * @param[in]	vw	品物の重さ・価値
 * @param[in]	weight	許容する重さの合計
 * @return	最大の価値の合計
 */
size_t
calculate(const std::vector<VW>& vw,
		  size_t weight)
{
	size_t max(0);
	std::vector<size_t> work(weight + 1, ~(size_t)0);
	work[0] = 0;

	for (auto t : vw) {
		for (size_t i(0); i < weight; ++i) {
			size_t j = weight - i - 1;
			if (work[j] == ~(size_t)0) continue;
			if (weight < j + t[1]) continue;
			if (work[j+t[1]] != ~(size_t)0
				&& work[j] + t[0] <= work[j+t[1]]) continue;
			work[j+t[1]] = work[j] + t[0];
			max = std::max(max, work[j+t[1]]);
		}
	}

	return max;
}

#define	N	4
#define	W	5

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector<VW> vw = {{{{4, 2}},
						   {{5, 2}},
						   {{2, 1}},
						   {{8, 3}}}};

	assert(vw.size() == N);

	std::printf("%lu\n", calculate(vw, W));

	return 0;
}
