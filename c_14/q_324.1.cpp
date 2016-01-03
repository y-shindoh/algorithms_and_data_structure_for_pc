/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_324.1.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.324の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  いくつかの属性を持つレコードの集合 (データベース) から、
  特定の属性の値が指定された領域に入るものを見つける問題を領域探索と呼びます。

  2次元の平面上の点の集合に対し、
  与えられた領域に含まれる点を列挙してください。
  ただし、与えられた点の集合に対して、点の追加・削除は行われません。
 */

/*
  メモ:
  書籍ではkD木を使って解いているが、ここではより簡単な方法で解いた。
  このため、最悪計算量が大きくなってしまっている。
 */

#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#define	M	6
#define	N	2

/**
 * サンプル・コマンド
 */
int
main()
{
	const int points[M][2] = {{2, 1},
							  {2, 2},
							  {4, 2},
							  {6, 2},
							  {3, 3},
							  {5, 4}};
	const int query[N][4] = {{2, 4, 0, 4},
							 {4, 10, 2, 5}};

	std::multimap<int, size_t> map[2];
	std::map<size_t, size_t> count;

	// O(M log M) の計算量
	for (size_t i(0); i < (size_t)M; ++i) {
		for (size_t j(0); j < 2; ++j) {
			map[j].insert(std::make_pair(points[i][j], i));
		}
	}

	// O(NM) の最悪計算量
	for (int i(0); i < N; ++i) {
		// O(M) の最悪計算量
		for (int j(0); j < 2; ++j) {
			auto it = map[j].lower_bound(query[i][j*2]);
			while (it != map[j].end() && it->first <= query[i][j*2+1]) {
				if (count.find(it->second) == count.end()) count[it->second] = 0;
				count[it->second]++;
				++it;
			}
		}

		// O(M) の最悪計算量
		for (auto it = count.begin(); it != count.end(); ++it) {
			if (it->second < 2) continue;
			std::printf("%lu\n", it->first);
		}
		std::printf("\n");

		count.clear();
	}

	return 0;
}
