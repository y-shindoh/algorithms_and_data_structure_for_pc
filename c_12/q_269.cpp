/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_269.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.269の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  グラフ G = (V, E) の表現方法には
  隣接リスト (adjacency list) と隣接行列 (adjacency matrices) による表現があります。

  隣接リスト表現では、
  V の各頂点に対して1個、合計 |V| 個のリスト Adj[|V|] でグラフを表します。
  頂点 u に対して、
  隣接リスト Adj[u] は E に属する全ての辺 (u, v_i) におけるすべての頂点 v_i を含んでいます。
  つまり、Adj[u] は G において u と隣接するすべての頂点からなります。

  一方、隣接行列表現では、
  頂点 i から頂点 j への辺がある場合 a_ij が1、ない場合0であるような
  |V| x |V| の行列 A でグラフを表します。

  隣接リスト表現の形式で与えられた有向グラフ G の
  隣接行列を出力するプログラムを作成してください。
  G は n (= |V|) 個の頂点を含み、
  それぞれ1からnまでの番号がふられているものとします。
 */

/*
  メモ:
  - 各数値を最初から0オリジンで扱っている。
  - 書籍では隣接行列表現を使っているが、ここでは隣接リスト表現を使う。
 */

#include <cstdio>
#include <vector>
#include <unordered_set>

#define	N	4

int
main()
{
	std::vector< std::unordered_set<size_t> > edges;
	edges.resize(N);

	edges[0].insert(1);
	edges[0].insert(3);
	edges[1].insert(3);
	edges[3].insert(2);

	for (size_t i(0); i < (size_t)N; ++i) {
		for (size_t j(0); j < (size_t)N; ++j) {
			if (0 < j) std::printf(" ");
			std::printf("%lu", edges[i].count(j));
		}
		std::printf("\n");
	}

	return 0;
}
