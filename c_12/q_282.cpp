/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_282.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.282の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた有向グラフ G = (V, E) について、
  頂点1から各頂点への最短距離d (パス上の辺の数の最小値) を
  求めるプログラムを作成してください。
  各頂点には1からnまでの番号がふられているものとします。
  頂点1からたどり着けない頂点については、距離として-1を出力してください。
 */

/*
  メモ:
  書籍では1オリジンだが、ここでは0オリジンとしている。
 */

#include <cstdio>
#include <set>
#include <vector>
#include <queue>

/*
 * 問題の回答
 * @param[in]	edges	隣接リスト
 * @param[in,out]	d	各頂点の距離
 * @param[in]	i	探索を開始する頂点
 */
void
bfs(const std::vector< std::set<size_t> >& edges,
	std::vector<size_t>& d,
	size_t i = 0)
{
	std::queue< std::pair<size_t, size_t> > queue;
	queue.push(std::pair<size_t, size_t>(i, 0));

	while(!queue.empty()) {
		auto v = queue.front();
		queue.pop();
		if (d[v.first] != ~(size_t)0) continue;
		d[v.first] = v.second;
		for (auto it = edges[v.first].begin(); it != edges[v.first].end(); ++it) {
			queue.push(std::pair<size_t, size_t>(*it, v.second + 1));
		}
	}
}

#define	N	4

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector< std::set<size_t> > edges(N);
	std::vector<size_t> d(N, ~(size_t)0);

	edges[0].insert(1);
	edges[0].insert(3);
	edges[1].insert(3);
	edges[3].insert(2);

	bfs(edges, d);

	for (int i(0); i < N; ++i) {
		if (d[i] != ~(size_t)0) {
			std::printf("%d %lu\n", i, d[i]);
		}
		else {
			std::printf("%d %d\n", i, -1);
		}
	}

	return 0;
}
