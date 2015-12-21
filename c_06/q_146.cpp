/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_146.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.146の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  整数nを入力し、深さnの再帰呼び出しによって生成される
  コッホ曲線の頂点の座標を出力するプログラムを作成してください。

  コッホ曲線はフラクタルの一種として知られています。
  フラクタルとは再帰的な構造を持つ図形のことで、
  以下のように再帰的な関数の呼び出しを用いて描画することができます。

  - 与えられた線分 (p1, p2) を3等分する。
  - 線分を3等分する2点s, tを頂点とする正三角形 (s, u, t) を生成する。
  - 線分 (p1, s)、線分 (s, u)、線分 (u, t)、線分 (t, p2) に対して、
    再帰的に同じ操作を繰り返す。
 */

/*
  メモ:
  正三角形の頂点を求める正しい方法 (回転) に気づかなかった。
  違う方法を考えてしまった。
 */

#include <cstdio>
#include <cmath>
#include <utility>

typedef	std::pair<double, double>	Point;	// 2次元の座標

/**
 * 2次元の点の座標を標準出力に出力
 * @param[in]	p	2次元の点
 */
void
write_point(const Point& p)
{
	std::printf("%f %f\n", p.first, p.second);
}

/**
 * コッホ曲線の新しい点の座標を標準出力に出力
 * @param[in]	p1	始点
 * @param[in]	p2	終点
 * @param[in]	n	再帰回数
 */
void
write_points_routine(const Point& p1,
					 const Point& p2,
					 size_t n)
{
	if (n == 0) return;

	Point s, u, t;
	const double d = M_PI / 3.0;

	s.first = (p1.first * 2.0 + p2.first * 1.0) / 3.0;
	s.second = (p1.second * 2.0 + p2.second * 1.0) / 3.0;
	t.first = (p1.first * 1.0 + p2.first * 2.0) / 3.0;
	t.second = (p1.second * 1.0 + p2.second * 2.0) / 3.0;
	u.first = (t.first - s.first) * std::cos(d) - (t.second - s.second) * std::sin(d) + s.first;
	u.second = (t.first - s.first) * std::sin(d) + (t.second - s.second) * std::cos(d) + s.second;

	write_point(s);
	write_point(u);
	write_point(t);

	--n;
	write_points_routine(p1, s, n);
	write_points_routine(s, u, n);
	write_points_routine(u, t, n);
	write_points_routine(t, p2, n);
}

/**
 * コッホ曲線の全ての点の座標を標準出力に出力
 * @param[in]	p1	始点
 * @param[in]	p2	終点
 * @param[in]	n	再帰回数
 */
void
write_points(const Point& p1,
			 const Point& p2,
			 size_t n)
{
	write_point(p1);
	write_points_routine(p1, p2, n);
	write_point(p2);
}

#define	N	1

/**
 * サンプル・コマンド
 */
int
main()
{
	Point p1(0.0, 0.0);
	Point p2(100.0, 0.0);

	write_points(p1, p2, N);

	return 0;
}
