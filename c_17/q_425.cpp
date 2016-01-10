/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_425.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.425の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  図のように、一辺が 1cm のタイルが、H x W個並べられています。
  タイルは汚れているもの、綺麗なもののいずれかです。

  綺麗なタイルのみを使ってできる正方形の面積の最大値を求めてください。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

/**
 * 問題の回答
 * @param[in]	board	H*Wのボード
 * @return	最大の正方形の面積
 */
size_t
search(const std::vector< std::vector<bool> >& board)
{
	size_t r(0);

	if (0 < board.size()) {
		std::vector<size_t> work[2];

		work[0].resize(board[0].size());
		work[1].resize(board[0].size(), 0);

		size_t i(0);
		size_t j;

		for (auto b : board) {
			j = 1 - i;
			for (size_t k(0); k < b.size(); ++k) {
				if (b[k]) {
					work[i][k] = 0;
				}
				else {
					work[i][k] = work[j][k] + 1;
					if (0 < k) {
						work[i][k] = std::min(work[i][k], work[i][k-1] + 1);
						work[i][k] = std::min(work[i][k], work[j][k-1] + 1);
					}
					r = std::max(r, work[i][k]);
				}
			}
			i = 1 - i;
		}
	}

	return r * r;
}

#define	H	4
#define	W	5

/**
 * サンプル・コマンド
 */
int
main()
{
	const std::vector< std::vector<bool> > table = {{{0, 0, 1, 0, 0},
													 {1, 0, 0, 0, 0},
													 {0, 0, 0, 0, 1},
													 {0, 0, 0, 1, 0}}};

	assert(table.size() == H);
	assert(table[0].size() == W);

	std::printf("%lu\n", search(table));

	return 0;
}
