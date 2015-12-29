/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_287.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.287の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  SNSの友達関係を入力し、双方向の友達リンクを経由して
  ある人からある人へたどりつけるかどうかを判定するプログラムを作成してください。
 */

/*
  メモ:
  - 実際のSNSにおける探索でも深さ優先探索が現実的でないと思われるため、
    ここでは幅優先探索で実装した。
  - 問題の性質上、各頂点から到達可能な頂点の情報を保持したほうが良いが、
    ここでは省略した。
 */

#include <cstdio>
#include <unordered_set>
#include <vector>
#include <queue>

/*
 * 問題の回答
 * @param[in]	edges	隣接リスト
 * @param[in]	s	探索を開始する頂点
 * @param[in]	e	探索を終了する頂点
 * @return	true: @a e まで到達, false: 未到達
 */
bool
bfs(const std::vector< std::unordered_set<size_t> >& edges,
	size_t s,
	size_t g)
{
	std::queue<size_t> queue;
	std::unordered_set<size_t> done;

	queue.push(s);

	while(!queue.empty()) {
		size_t i = queue.front();
		queue.pop();
		if (done.find(i) != done.end()) continue;
		if (i == g) return true;
		for (auto it = edges[i].begin(); it != edges[i].end(); ++it) {
			queue.push(*it);
		}
	}

	return false;
}

#define	L	10
#define	M	9
#define	N	3

/**
 * サンプル・コマンド
 */
int
main()
{
	std::vector< std::unordered_set<size_t> > edges(L);

	size_t a[M][2] = {{0, 1},
					  {0, 2},
					  {3, 4},
					  {5, 7},
					  {5, 6},
					  {6, 7},
					  {6, 8},
					  {7, 8},
					  {8, 9}};
	size_t b[N][2] = {{0, 1},
					  {5, 9},
					  {1, 3}};

	for (int i(0); i < M; ++i) {
		edges[a[i][0]].insert(a[i][1]);
	}

	for (int i(0); i < N; ++i) {
		std::printf("%s\n", bfs(edges, b[i][0], b[i][1]) ? "yes" : "no");
	}

	return 0;
}
