/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_348.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.348の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  無向グラフGにおいて、
  頂点uと、uから出ている全てのエッジを削除して得られる部分グラフが、
  非連結になるとき、
  頂点uをグラフGの関節点 (Articulation Point) または切断点と言います。
  例えば上の図のグラフ (省略) では、灰色の頂点が関節点になります。
 */

/*
  メモ:
  自力では解けず、書籍の説明を読んでコーディングした。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>

/**
 * 関節点探索の補助関数
 * @param[in]	graph	隣接リスト
 * @param[in,out]	parent	DFSにおける各要素の親
 * @param[in,out]	reach	DFSにおける到達順
 * @param[out]	score	スコア (算出方式はコードを参照)
 * @param[in]	i	処理対象のノード
 * @param[in]	n	DFSにおける到達順
 * @return	処理対象のノードのスコア (算出方式はコードを参照)
 */
template<typename TYPE>
size_t
search(const std::vector< std::set<TYPE> >& graph,
	   std::vector<TYPE>& parent,
	   std::vector<TYPE>& reach,
	   std::vector<TYPE>& score,
	   TYPE i,
	   TYPE& n)
{
	assert(i < graph.size());

	reach[i] = score[i] = n++;

	for (TYPE j : graph[i]) {
		if (reach[j] == ~(TYPE)0) {
			parent[j] = i;
			score[i] = std::min(score[i], search(graph, parent, reach, score, j, n));
		}
		else if (parent[i] != j) {
			score[i] = std::min(score[i], reach[j]);	// バック・エッジ処理
		}
	}

	return score[i];
}

/**
 * 関節点探索
 * @param[in]	graph	隣接リスト
 * @param[out]	result	関節点
 */
template<typename TYPE>
void
search(const std::vector< std::set<TYPE> >& graph,
	   std::set<TYPE>& result)
{
	std::vector<TYPE> parent(graph.size(), ~(TYPE)0);
	std::vector<TYPE> reach(graph.size(), ~(TYPE)0);
	std::vector<TYPE> score(graph.size(), ~(TYPE)0);
	TYPE n(0);

	search<TYPE>(graph, parent, reach, score, 0, n);

	assert(graph.size() == n);

	// ルート
	TYPE c(0);
	for (TYPE i : parent) { if (i == 0) c++; };
	if (1 < c) result.insert(0);

	// ルート以外
	for (size_t i(0); i < parent.size(); ++i) {
		if (parent[i] == 0) continue;
		if (parent[i] == ~(TYPE)0) continue;
		if (reach[parent[i]] > score[i]) continue;
		result.insert(parent[i]);
	}
}

#define	N	4
//#define	N	8

/**
 * 無向グラフの隣接リスト作成の補助関数
 */
void
add_edge(std::vector< std::set<size_t> >& graph,
		 size_t i,
		 size_t j)
{
	graph[i].insert(j);
	graph[j].insert(i);
}

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector< std::set<size_t> > graph(N);
	std::set<size_t> result;

	add_edge(graph, 0, 1);
	add_edge(graph, 0, 2);
	add_edge(graph, 1, 2);
	add_edge(graph, 2, 3);

//	add_edge(graph, 0, 1);
//	add_edge(graph, 0, 2);
//	add_edge(graph, 0, 3);
//	add_edge(graph, 1, 2);
//	add_edge(graph, 2, 3);
//	add_edge(graph, 3, 4);
//	add_edge(graph, 3, 5);
//	add_edge(graph, 5, 6);
//	add_edge(graph, 5, 7);
//	add_edge(graph, 6, 7);

	search(graph, result);

	for (size_t v : result) { std::printf("%lu\n", v); }

	return 0;
}
