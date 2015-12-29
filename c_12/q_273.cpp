/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_273.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.273の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  深さ優先探索 (Depth First Search: DFS) は、可能な限り隣接する頂点を訪問する、
  という戦略に基づくグラフの探索アルゴリズムです。
  未探索の接続辺が残されている頂点の中で
  最後に発見した頂点 v の接続辺を再帰的に探索します。
  v の辺をすべて探索し終えると、
  v を発見したときに通ってきた辺を後戻りして探索を続行します。

  探索は元の視点から到達可能なすべての頂点を発見するまで続き、
  未発見の頂点が残っていれば、
  その中の番号が一番小さい1つを新たな始点として探索を続けます。

  深さ優先探索では、各頂点に以下のタイムスタンプを推します:
  - タイムスタンプ d[v]: v を最初に訪問した発見時刻を記録します。
  - タイムスタンプ f[v]: v の隣接リストを調べ終えた完了時刻を記録します。

  以下の仕様に基づき、
  与えられた有向グラフ G = (V, E) に対する
  深さ優先探索の動作を示すプログラムを作成してください:
  - G は隣接リスト表現の形式で与えられます。
    拡張点には1からnまでの番号がふられています。
  - 各隣接リストの頂点は番号が小さい順に並べられています。
  - プログラムは各頂点の発見時刻と完了時刻を報告します。
  - 深さ優先探索の課程において、
    訪問する頂点の候補が複数ある場合は頂点番号が小さいものから選択します。
  - 最初に訪問する頂点の開始時刻を1とします。
 */

/*
  メモ:
  - 書籍は1オリジンだが、ここでは0オリジンで実装した。
  - 書籍では探索の末端で折り返す際に余分に1つ時刻を増やしているが、
    ここではそれを避けている。
 */

#include <cstdio>
#include <set>
#include <vector>

/**
 * 問題の回答 (再帰処理版)
 * @param[in]	edges	隣接リスト
 * @param[in,out]	done	訪問済み頂点群
 * @param[out]	d	初回訪問時刻
 * @param[out]	f	最終訪問時刻
 * @param[in]	i	探索対象の頂点
 * @param[in,out]	t	時刻
 * @return	true: 探索完了, false: 探索中
 */
bool
dfs(const std::vector< std::set<size_t> >& edges,
	std::set<size_t>& done,
	std::vector<size_t>& d,
	std::vector<size_t>& f,
	size_t i,
	size_t& t)
{
	++t;	// 到着
	if (d[i] == 0) {
		d[i] = t;
		done.insert(i);
	}

	if (done.size() < d.size()) {
		for (auto it = edges[i].begin(); it != edges[i].end(); ++it) {
			bool r = dfs(edges, done, d, f, *it, t);
			++t;	// 戻ってきた
			if (r) break;
		}
	}

	//++t;	// 離脱
	if (f[i] < t) f[i] = t;

	return done.size() == d.size();
}

#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector< std::set<size_t> > edges(N);
	std::set<size_t> done;
	std::vector<size_t> d(N, 0);
	std::vector<size_t> f(N, 0);
	size_t t(0);

	edges[0].insert(1);
	edges[0].insert(2);
	edges[1].insert(2);
	edges[1].insert(3);
	edges[2].insert(4);
	edges[3].insert(5);
	edges[4].insert(5);

	dfs(edges, done, d, f, 0, t);

	for (int i(0); i < N; ++i) {
		std::printf("%d %lu %lu\n", i, d[i], f[i]);
	}

	return 0;
}
