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
 * @param[in]	length	品物の種類
 * @param[in]	weight	許容する重さの合計
 * @return	最大の価値の合計
 */
size_t
calculate(const VW* vw,
		  size_t length,
		  size_t weight)
{
	assert(vw);

	size_t max(0);
	std::vector<size_t> work(weight + 1, ~(size_t)0);
	work[0] = 0;

	for (size_t i(0); i < length; ++i) {
		for (size_t j(0); j < weight; ++j) {
			size_t k = weight - j - 1;
			if (work[k] == ~(size_t)0) continue;
			if (weight < k + vw[i][1]) continue;
			if (work[k+vw[i][1]] != ~(size_t)0
				&& work[k] + vw[i][0] <= work[k+vw[i][1]]) continue;
			work[k+vw[i][1]] = work[k] + vw[i][0];
			max = std::max(max, work[k+vw[i][1]]);
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
	const size_t vw[N][2] = {{4, 2},
							 {5, 2},
							 {2, 1},
							 {8, 3}};
	std::vector<VW> input;

	for (size_t i(0); i < N; ++i) {
		input.push_back(VW{{vw[i][0], vw[i][1]}});
	}

	std::printf("%lu\n", calculate(&input[0], input.size(), W));

	return 0;
}
