/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_318.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.318の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  互いに素な動的集合 S = {S_1, S_2, ..., S_k} を管理するプログラムを作成してください。

  まず、整数 n を読み込み、
  0, 1, ..., n-1 をそれぞれ唯一の要素とする n 個の互いに素な集合を作成します。

  次に、整数 q を読み込み、q 個のクエリに応じて集合を操作します。
  クエリは以下の2種類を含みます。
  - unite(x, y): x を含む集合 S_x と y を含む集合 S_y を合併する。
  - same(x, y): x と y が同じ集合に属しているかを判定する。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

/**
 * union find tree
 */
template<typename TYPE>
class UnionFindTree
{
private:

	std::vector<TYPE> parent_;	///< 集合の代表元 or それに準じる元
	std::vector<TYPE> rank_;	///< 集合の木表現における深さ

	/**
	 * 代表元の取得
	 * @param[in]	i	集合の元
	 * @return	集合の代表元
	 */
	TYPE
	find(const TYPE& i)
		{
			assert(i < parent_.size());

			if (parent_[i] != i) parent_[i] = find(parent_[i]);

			return parent_[i];
		}

public:

	/**
	 * コンストラクタ
	 * @param[in]	n	初期の集合の総数
	 */
	UnionFindTree(const TYPE& n)
		: parent_(n), rank_(n, 1)
		{
			for (TYPE i(0); i < n; ++i) {
				parent_[i] = i;
			}
		}

	/**
	 * 集合の統合
	 * @param[in]	i	集合の元
	 * @param[in]	j	集合の元
	 */
	void
	unite(TYPE i,
		  TYPE j)
		{
			assert(i < parent_.size());
			assert(j < parent_.size());

			i = find(i);
			j = find(j);

			if (rank_[i] < rank_[j]) std::swap(i, j);
			if (rank_[i] == rank_[j]) rank_[i]++;

			parent_[j] = i;
		}

	/**
	 * 2つの元が同一集合の属するか確認
	 * @param[in]	i	集合の元
	 * @param[in]	j	集合の元
	 * @return	true: 属する, false: 属さない
	 */
	bool
	same(const TYPE& i,
		 const TYPE& j)
		{
			assert(i < parent_.size());
			assert(j < parent_.size());

			return find(i) == find(j);
		}
};

#define	N	12

/**
 * サンプル・コマンド
 */
int
main()
{
	const unsigned int command[N][3] = {{0, 1, 4},
										{0, 2, 3},
										{1, 1, 2},
										{1, 3, 4},
										{1, 1, 4},
										{1, 3, 2},
										{0, 1, 3},
										{1, 2, 4},
										{1, 3, 0},
										{0, 0, 4},
										{1, 0, 2},
										{1, 3, 0}};
	UnionFindTree<unsigned int> uft(N);

	for (int i(0); i < N; ++i) {
		switch (command[i][0]) {
		case 0:
			uft.unite(command[i][1], command[i][2]);
			break;
		case 1:
			std::printf("%d\n", (int)uft.same(command[i][1], command[i][2]));
			break;
		default:
			assert(false);
			break;
		}
	}

	return 0;
}
