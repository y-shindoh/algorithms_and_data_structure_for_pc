/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_461.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.461の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  15パズルは図のような1つの空白を含む4x4のマス上に15枚のパネルが配置され、
  空白を使ってパネルを上下左右にスライドさせ、絵柄を揃えるパズルです。

  この問題では、次のように空白を0、
  各パネルを1から15の番号でパズルを表します。

  1  2  3  4
  6  7  8  0
  5 10 11 12
  9 13 14 15

  1回の操作で空白の方向に1つのパネルを移動することができ、
  ゴールは次のようなパネルの配置とします。

   1  2  3  4
   5  6  7  8
   9 10 11 12
  13 14 15  0

  15パズルの初期状態が与えられるので、
  ゴールまでの最短手順を求めるプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <tuple>
#include <queue>

/**
 * 15パズルの盤
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
	 * ゴールの状態との差分を算出
	 * @return	ゴールの状態との差分
	 */
	size_t
	check() const
		{
			size_t d(0);

			for (size_t i(0); i < N * N; ++i) {
				if (data_[i] != 0) {
					if (data_[i] < i + 1) d += (i + 1) - data_[i];
					else d += data_[i] - (i + 1);
				}
				else {
					d += (N * N - 1) - i;
				}
			}

			return d;
		}

	/**
	 * 比較演算子 (std::priority_queue で用いる)
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
 * 15パズルの最短手順を算出 (A*)
 * @param[in]	board	盤
 * @return	最短手順
 * @note	コードの重複はスルー。
 */
template<typename TYPE, size_t N>
size_t
search(const Board<TYPE, N>& board)
{
	// ゴールまでの差分, 今までの手数, ボードの状態, 0の行, 0の列
	typedef std::tuple<size_t, size_t, Board<TYPE, N>, size_t, size_t> Unit;

	std::priority_queue< Unit, std::vector<Unit>, std::greater<Unit> > queue;

	for (size_t i(0); i < N; ++i) {
		for (size_t j(0); j < N; ++j) {
			if (board.get(i, j) != 0) continue;
			size_t c = board.check();
			if (c == 0) return 0;
			queue.push(Unit(c, 0, board, i, j));
			break;
		}
		if (0 < queue.size()) break;
	}

	while (0 < queue.size()) {
		size_t n = std::get<1>(queue.top());
		Board<TYPE, N> b = std::get<2>(queue.top());
		size_t i = std::get<3>(queue.top());
		size_t j = std::get<4>(queue.top());
		queue.pop();
		if (0 < i) {
			b.swap(i, j, i - 1, j);
			size_t c = b.check();
			if (c == 0) return n + 1;
			queue.push(Unit(c + n, n + 1, b, i - 1, j));
			b.swap(i, j, i - 1, j);
		}
		if (i + 1 < N) {
			b.swap(i, j, i + 1, j);
			size_t c = b.check();
			if (c == 0) return n + 1;
			queue.push(Unit(c + n, n + 1, b, i + 1, j));
			b.swap(i, j, i + 1, j);
		}
		if (0 < j) {
			b.swap(i, j, i, j - 1);
			size_t c = b.check();
			if (c == 0) return n + 1;
			queue.push(Unit(c + n, n + 1, b, i, j - 1));
			b.swap(i, j, i, j - 1);
		}
		if (j + 1 < N) {
			b.swap(i, j, i, j + 1);
			size_t c = b.check();
			if (c == 0) return n + 1;
			queue.push(Unit(c + n, n + 1, b, i, j + 1));
			b.swap(i, j, i, j + 1);
		}
	}

	assert(false);

	return ~(size_t)0;
}

#define	N	4

/**
 * サンプル・コマンド
 */
int
main()
{
	char b[N][N] = {{1,  2,  3,  4},
					{6,  7,  8,  0},
					{5, 10, 11, 12},
					{9, 13, 14, 15}};
	Board<char, N> board(b);

	std::printf("%lu\n", search(board));

	return 0;
}
