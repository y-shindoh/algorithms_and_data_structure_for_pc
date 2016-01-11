/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_428.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.428の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  図 (省略) のように、一辺が1cmのタイルが、H x W個並べられています。
  タイルは汚れているもの、綺麗なもののいずれかです。

  綺麗なタイルのみを使ってできる長方形の面積の最大値を求めてください。
 */

#include <cstdio>
#include <cassert>
#include <array>
#include <vector>

/**
 * 問題の回答
 * @param[in]	board	H*Wのボード
 * @return	最大の長方形の面積
 */
size_t
search(const std::vector< std::vector<bool> >& board)
{
	std::vector<size_t> work[2];
	std::vector< std::array<size_t, 2> > stack;	// h, w
	size_t r(0);

	work[0].resize(board[0].size());
	work[1].resize(board[0].size(), 0);

	size_t i(0);
	size_t j;

	for (auto b : board) {
		j = 1 - i;
		for (size_t k(0); k < b.size(); ++k) {
			if (b[k]) {
				work[i][k] = 0;
				stack.clear();
			}
			else {
				work[i][k] = work[j][k] + 1;
				size_t t(k);
				while (0 < stack.size() && work[i][k] <= stack.back()[0]) {
					t = stack.back()[1];
					stack.pop_back();
				}
				stack.push_back({{work[i][k], t}});
				for (auto v : stack) {
					r = std::max(r, (k - v[1] + 1) * v[0]);
				}
			}
		}
		i = 1 - i;
		stack.clear();
	}

	return r;
}

#define	H	4
#define	W	5

/**
 * サンプル・コマンド
 */
int
main()
{
	const std::vector< std::vector<bool> > board = {{{0, 0, 1, 0, 0},
													 {1, 0, 0, 0, 0},
													 {0, 0, 0, 1, 0},
													 {0 ,0, 0, 1, 0}}};

	assert(board.size() == H);
	assert(board[0].size() == W);

	std::printf("%lu\n", search(board));

	return 0;
}
