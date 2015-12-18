/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_114.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.114の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  地域の治水対策として、洪水の被害状況をシミュレーションで仮想してみよう。
  図のように 1×1 (m^2) の区画からなる格子上に表された地域の模式断面図が与えられるので、
  地域にできる各水たまりの面積を報告してください。

  与えられた地域に対して限りなく雨が降り、
  地域から溢れ出た水は左右の海に流れ出ると仮定します。
  例えば、図の断面積では、左から面積が4, 2, 1, 19 の水たまりができます。
 */

/*
  メモ:
  自力ではきれいな解き方ができなかった。
 */

#include <cstdio>
#include <cassert>
#include <stack>
#include <vector>
#include <utility>

typedef	std::pair<size_t, size_t>	LeftQuantity;	// 左端と量

/**
 * 問題の回答
 * @param[in]	input	上り・下り・水平を示す文字列
 * @param[out]	output	個別の水たまりの水量
 */
void
calculate_water(const char* input,
				std::vector<size_t>& output)
{
	assert(input);

	std::stack<size_t> l_stack;				// 下りの文字列の位置
	std::vector<LeftQuantity> lq_vector;	// 水たまりの左端と量
	size_t l;
	size_t t;

	for (size_t i(0); input[i]; ++i) {
		switch (input[i]) {
		case 'd':
			l_stack.push(i);
			break;
		case 'u':
			if (0 < l_stack.size()) {
				l = l_stack.top();
				l_stack.pop();
				t = i - l;
				while (0 < lq_vector.size() && l < lq_vector.back().first) {
					t += lq_vector.back().second;
					lq_vector.pop_back();
				}
				lq_vector.push_back(std::make_pair(l, t));
			}
			break;
		}
	}

	output.clear();

	for (auto i = lq_vector.begin(); i != lq_vector.end(); ++i) {
		output.push_back(i->second);
	}
}

/**
 * サンプル・コマンド
 */
int
main()
{
	const char input[] = "dduuud_ududdddu_udduuu_ddd_ddu_du_ud";
	std::vector<size_t> output;
	size_t r(0);

	calculate_water(input, output);

	for (auto i = output.begin(); i != output.end(); ++i) r += *i;
	std::printf("%lu\n", r);
	std::printf("%lu", output.size());
	for (auto i = output.begin(); i != output.end(); ++i) std::printf(" %lu", *i);
	std::printf("\n");

	return 0;
}
