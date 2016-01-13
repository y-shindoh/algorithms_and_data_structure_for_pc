/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_455.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.455の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  8パズルは図のような1つの空白を含む3x3のマス上に8枚のパネルが配置され、
  空白を使ってパネルを上下左右にスライドさせ、絵柄を揃えるパズルです。

  この問題では、次のように空白を0、
  各パネルを1から8の番号でパズルを表します。

  1 3 0
  4 2 5
  7 8 6

  1回の操作で空白の方向に1つのパネルを移動することができ、
  ゴールは次のようなパネルの配置とします。

  1 2 3
  4 5 6
  7 8 0

  8パズルの初期状態が与えられるので、
  ゴールまでの最短手順を求めるプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <tuple>
#include <queue>
#include <set>

/**
 * 8パズルの盤
 */
template<typename TYPE, size_t N>
class Board
{
private:

	TYPE data_[N*N];	///< 盤の状態

public:

	/**
	 * コンストラクタ
	 */
	Board(const TYPE board[N][N])
		{
			std::memcpy((void*)data_, (const void*)board, sizeof(TYPE) * N * N);
		}

	/**
	 * コピー・コンストラクタ
	 */
	Board(const Board<TYPE, N>& board)
		{
			std::memcpy((void*)data_, (const void*)board.data_, sizeof(TYPE) * N * N);
		}

	/**
	 * 指定位置の値を取得
	 * @param[in]	i	行
	 * @param[in]	j	列
	 * @return	指定位置の値
	 */
	TYPE
	get(size_t i,
		size_t j) const
		{
			assert(i < N);
			assert(j < N);

			return data_[i * N + j];
		}

	/**
	 * 指定位置の値を交換
	 * @param[in]	i1	1つ目の要素の行
	 * @param[in]	j1	1つ目の要素の列
	 * @param[in]	i2	2つ目の要素の行
	 * @param[in]	j2	2つ目の要素の列
	 */
	void
	swap(size_t i1,
		 size_t j1,
		 size_t i2,
		 size_t j2)
		{
			assert(i1 < N);
			assert(j1 < N);
			assert(i2 < N);
			assert(j2 < N);

			std::swap(data_[i1 * N + j1], data_[i2 * N + j2]);
		}

	/**
	 * ゴールの状態か否かを確認
	 * @return	true: ゴールの状態, false: ゴールの状態でない
	 */
	bool
	check() const
		{
			for (size_t i(1); i < N * N; ++i) {
				if (data_[i-1] != (TYPE)i) return false;
			}

			return data_[N*N-1] == 0;
		}

	/**
	 * 比較演算子 (std::set で用いる)
	 */
	bool
	operator < (const Board<TYPE, N>& b) const
		{
			for (size_t i(0); i < N * N; ++i) {
				if (data_[i] == b.data_[i]) continue;
				return data_[i] < b.data_[i];
			}

			return false;
		}
};

/**
 * 8パズルの最短手順を算出
 * @param[in]	board	盤
 * @return	最短手順
 */
template<typename TYPE, size_t N>
size_t
search(const Board<TYPE, N>& board)
{
	typedef std::tuple<Board<TYPE, N>, size_t, size_t> Unit;

	std::set< Board<TYPE, N> > done;
	std::queue<Unit> queue[2];

	for (size_t i(0); i < N; ++i) {
		for (size_t j(0); j < N; ++j) {
			if (board.get(i, j) != 0) continue;
			queue[0].push(Unit(board, i, j));
			break;
		}
		if (0 < queue[0].size()) break;
	}

	for (size_t i(0); true; ++i) {
		size_t h = i % 2;
		size_t k = 1 - h;
		while (0 < queue[h].size()) {
			Board<TYPE, N> b = std::get<0>(queue[h].front());
			size_t ti = std::get<1>(queue[h].front());
			size_t tj = std::get<2>(queue[h].front());
			queue[h].pop();
			if (done.find(b) != done.end()) continue;
			if (b.check()) return i;
			done.insert(b);
			if (0 < ti) {
				queue[k].push(Unit(b, ti - 1, tj));
				std::get<0>(queue[k].back()).swap(ti, tj, ti - 1, tj);
			}
			if (ti + 1 < N) {
				queue[k].push(Unit(b, ti + 1, tj));
				std::get<0>(queue[k].back()).swap(ti, tj, ti + 1, tj);
			}
			if (0 < tj) {
				queue[k].push(Unit(b, ti, tj - 1));
				std::get<0>(queue[k].back()).swap(ti, tj, ti, tj - 1);
			}
			if (tj + 1 < N) {
				queue[k].push(Unit(b, ti, tj + 1));
				std::get<0>(queue[k].back()).swap(ti, tj, ti, tj + 1);
			}
		}
		if (queue[k].empty()) break;
	}

	assert(false);

	return ~(size_t)0;
}

#define	N	3

/**
 * サンプル・コマンド
 */
int
main()
{
	char b[N][N] = {{1, 3, 0},
					{4, 2, 5},
					{7, 8, 6}};
	Board<char, N> board(b);

	std::printf("%lu\n", search(board));

	return 0;
}
