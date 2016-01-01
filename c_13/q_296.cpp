/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_296.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.296の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた重み付きグラフ G = (V, E) に対する
  最小全域木の辺の重みの総和を計算するプログラムを作成してください。
 */

/*
  メモ:
  計算時間を考えるとクラスカル法で実装すべきだが、
  まだ union find tree の話題が出ていないのでプリム法で実装した。
 */

#include <cstdio>
#include <tuple>
#include <queue>
#include <vector>
#include <unordered_set>

typedef	std::tuple<size_t, size_t>	CV;	///< 重みと頂点

/*
 * 隣接行列から最小全域木を生成した場合のコストの合計値を算出
 * @param[in]	edges	隣接行列
 * @param[in]	s	探索を開始する頂点
 * @return	最小全域木を生成した場合のコストの合計値
 */
template<size_t N>
size_t
calculate(const int edges[N][N],
		  size_t s)
{
	std::priority_queue< CV, std::vector<CV>, std::greater<CV> > queue;
	std::unordered_set<size_t> done;
	size_t r(0);

	queue.push(CV(s, 0));

	while (!queue.empty()) {
		CV cv = queue.top();
		queue.pop();
		size_t i = std::get<1>(cv);
		if (done.find(i) != done.end()) continue;
		done.insert(i);
		r += std::get<0>(cv);
		for (size_t j(0); j < N; ++j) {
			if (edges[i][j] < 0) continue;
			queue.push(CV((size_t)edges[i][j], j));
		}
	}

	return r;
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

	std::printf("%lu\n", calculate(E, 0));

	return 0;
}
