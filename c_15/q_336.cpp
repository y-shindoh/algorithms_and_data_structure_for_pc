/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_336.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.336の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  重み付き有向グラフ G = (V, E) の全点対間最短経路の距離を列挙してください。
 */

/*
  メモ:
  全ての頂点の間の最短経路を求めるため、
  ワーシャル・フロイド法が最適と判断できる。
 */

#include <cstdio>
#include <climits>
#include <cassert>
#include <algorithm>

/**
 * ワーシャル・フロイド法による最短経路の解決
 * @param[in,out]	table	全経路の距離
 */
template<size_t N>
void
search(int table[N][N])
{
	for (size_t i(0); i < N; ++i) {
		for (size_t j(0); j < N; ++j) {
			for (size_t k(0); k < N; ++k) {
				if (table[i][k] == INT_MAX) continue;
				if (table[k][j] == INT_MAX) continue;
				table[i][j] = std::min(table[i][j], table[i][k] + table[k][j]);
			}
		}
	}
}

/**
 * スコアが負の頂点がないかを確認
 * @param[in]	table	全経路の距離
 * @return	true: ない, false: ある
 * @note	返却値が false の場合、負の閉路が存在する。
 */
template<size_t N>
bool
check(const int table[N][N])
{
	for (size_t i(0); i < N; ++i) {
		if (table[i][i] < 0) return false;
	}

	return true;
}

#define	M	4
#define	N	6

/**
 * サンプル・コマンド
 */
int
main()
{
	int table[M][M];
//	const int graph[N][3] = {{0, 1, 1},
//							 {0, 2, 5},
//							 {1, 2, 2},
//							 {1, 3, 4},
//							 {2, 3, 1},
//							 {3, 2, 7}};
	const int graph[N][3] = {{0, 1, 1},
							 {0, 2, -5},
							 {1, 2, 2},
							 {1, 3, 4},
							 {2, 3, 1},
							 {3, 2, 7}};
//	const int graph[N][3] = {{0, 1, 1},
//							 {0, 2, 5},
//							 {1, 2, 2},
//							 {1, 3, 4},
//							 {2, 3, 1},
//							 {3, 2, -7}};

	for (int i(0); i < M; ++i) {
		std::fill(table[i], table[i] + M, INT_MAX);
		table[i][i] = 0;
	}

	for (int i(0); i < N; ++i) {
		assert(graph[i][0] < N);
		assert(graph[i][1] < N);
		table[graph[i][0]][graph[i][1]] = graph[i][2];
	}

	search<M>(table);

	if (check<M>(table)) {
		for (auto t : table) {
			for (int i(0); i < M; ++i) {
				if (0 < i) std::printf(" ");
				if (t[i] != INT_MAX) {
					std::printf("%d", t[i]);
				}
				else {
					std::printf("INF");
				}
			}
			std::printf("\n");
		}
	}
	else {
		printf("NEGATIVE CYCLE\n");
	}

	return 0;
}
