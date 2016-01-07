/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_353.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.353の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  非負の重みを持つ無向の木Tの直径を求めてください。
  木の最遠節点間の距離を着の直径と言います。
 */

/*
  メモ:
  書籍では幅優先探索で実装しているが、ここでは深さ優先探索で実装した。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>

/**
 * 木の直径を算出
 * @param[in]	graph	木の隣接リスト
 * @param[in,out]	done	到達済みノード
 * @param[in,out]	width	直径 (の最大値)
 * @param[in]	depth	処理対象ノードの深さ
 * @param[in]	index	処理対象ノード
 * @return	処理対象ノードの高さ
 */
size_t
search(const std::vector< std::map<size_t, size_t> >& graph,
	   std::unordered_set<size_t>& done,
	   size_t& width,
	   size_t depth = 0,
	   size_t index = 0)
{
	assert(index < graph.size());

	size_t queue[2] = {0, depth};
	size_t t;

	for (auto e : graph[index]) {
		if (done.find(e.first) != done.end()) continue;
		done.insert(e.first);
		t = search(graph, done, width, depth + e.second, e.first) + e.second;
		if (t <= queue[0]) continue;
		queue[0] = t;
		if (queue[1] < t) std::swap(queue[0], queue[1]);
	}

	width = std::max(width, queue[0] + queue[1]);

	return depth != queue[1] ? queue[1] : queue[0];
}

#define	N	4

/**
 * 無向グラフの隣接リスト作成の補助関数
 */
void
add_edge(std::vector< std::map<size_t, size_t> >& graph,
		 size_t i,
		 size_t j,
		 size_t w)
{
	graph[i].insert(std::make_pair(j, w));
	graph[j].insert(std::make_pair(i, w));
}

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector< std::map<size_t, size_t> > graph(N);
	std::unordered_set<size_t> done;
	size_t w(0);

	add_edge(graph, 0, 1, 2);
	add_edge(graph, 1, 2, 1);
	add_edge(graph, 1, 3, 3);

//	add_edge(graph, 0, 1, 1);
//	add_edge(graph, 1, 2, 2);
//	add_edge(graph, 2, 3, 4);

	search(graph, done, w);

	std::printf("%lu\n", w);

	return 0;
}
