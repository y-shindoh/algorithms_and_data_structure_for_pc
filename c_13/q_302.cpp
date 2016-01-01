/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_302.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.302の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた重み付き有向グラフ G = (V, E) について、
  単一始点最短経路のコストを求めるプログラムを作成してください。
  G の頂点 0 を始点とし、0 から各頂点 v について、
  最短経路上の辺の重みの総和 d[v] を出力してください。
 */

/*
  メモ:
  重みが非負であることから、ダイクストラ法を用いて実装した。
 */

#include <cstdio>
#include <tuple>
#include <queue>
#include <vector>

typedef	std::tuple<size_t, size_t>	CV;	///< 重みの和と頂点

/*
 * 隣接行列から単一始点最短経路を算出
 * @param[in]	edges	隣接行列
 * @param[in,out]	costs	各頂点の最短経路の重み合計値
 * @param[in]	s	始点
 */
template<size_t N>
void
calculate(const int edges[N][N],
		  size_t* costs,
		  size_t s)
{
	std::priority_queue< CV, std::vector<CV>, std::greater<CV> > queue;

	queue.push(CV(s, 0));

	while (!queue.empty()) {
		CV cv = queue.top();
		queue.pop();
		size_t i = std::get<1>(cv);
		if (costs[i] != ~(size_t)0) continue;
		costs[i] = std::get<0>(cv);
		for (size_t j(0); j < N; ++j) {
			if (edges[i][j] < 0) continue;
			queue.push(CV(costs[i] + (size_t)edges[i][j], j));
		}
	}
}

#define	N	5

/**
 * サンプル・コマンド
 */
int
main()
{
	const int E[N][N] = {{-1, 2, 3, 1, -1},
						 {2, -1, -1, 4, -1},
						 {3, -1, -1, 1, 1},
						 {1, 4, 1, -1, 3},
						 {-1, -1, 1, 3, -1}};
	size_t d[N];

	std::fill(d, d + N, ~(size_t)0);
	calculate(E, d, 0);

	for (int i(0); i < N; ++i) {
		std::printf("%d %lu\n", i, d[i]);
	}

	return 0;
}
