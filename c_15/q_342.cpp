/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_342.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.342の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  閉路のない有向グラフDAGは
  物事の手順を表すデータ構造として応用することができます。
  例えば、各仕事を頂点、仕事の順序を有効辺で表すことができます。
  上の図では、仕事Bに着手するためには、
  仕事Aと仕事Xの両方が完了している必要があります。
  このような関係を表すDAGに対して、トポロジカルソートを行うと、
  着手すべき順序に仕事を列挙することができます。
  DAGの各辺 (u, v) について、
  uがvよりも先に位置するように並べることを、トポロジカルソートと言います。

  与えられたDAG Gに対して、
  トポロジカルソートを行った頂点の並びを出力してください。
 */

/*
  メモ:
  幅優先探索の使い方が書籍と違うので、出力が一致しない。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

/**
 * トポロジカル・ソート
 * @param[in]	graph	隣接リスト ([to][*] => from の形式)
 * @param[out]	out	ソート結果
 */
void
topological_sort(const std::vector< std::vector<size_t> >& graph,
				 std::deque<size_t>& out)
{
	std::vector<size_t> counts(graph.size(), 0);

	for (size_t i(0); i < graph.size(); ++i) {
		for (size_t j : graph[i]) counts[j]++;
	}

	std::queue<size_t> queue;

	for (size_t i(0); i < graph.size(); ++i) {
		if (0 < counts[i]) continue;
		out.push_front(i);
		queue.push(i);
	}

	while (0 < queue.size()) {
		size_t i = queue.front();
		queue.pop();
		for (size_t j : graph[i]) {
			if (0 < --counts[j]) continue;
			out.push_front(j);
			queue.push(j);
		}
	}

	assert(graph.size() == out.size());	// 閉路のチェック
}

#define	M	6
#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	const size_t graph[N][2] = {{0, 1},
								{1, 2},
								{3, 1},
								{3, 4},
								{4, 5},
								{5, 2}};
	std::vector< std::vector<size_t> > rgraph(M);
	std::deque<size_t> out;

	for (int i(0); i < N; ++i) {
		assert(graph[i][0] < M);
		assert(graph[i][1] < M);
		rgraph[graph[i][1]].push_back(graph[i][0]);
	}

	topological_sort(rgraph, out);

	for (size_t v : out) std::printf("%lu\n", v);

	return 0;
}
