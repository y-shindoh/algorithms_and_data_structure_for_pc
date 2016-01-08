/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_374.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.374の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  直線 s1, s2 について、
  それらが並行な場合 "2"、直行する場合 "1"、それ以外の場合 "0" と出力してください。
  s1 は点 p0, p1 を通り、s2 は点 p2, p3 を通ります。
 */

#include <cstdio>
#include <cmath>

/**
 * 平面上の点を表現するクラス
 * @note	後述の要領で、原点を始点と考えたベクトルも表現させる。
 */
template<typename TYPE>
class Point
{
public:

	TYPE x_;	///< x軸の要素
	TYPE y_;	///< y軸の要素

	/**
	 * コンストラクタ
	 * @param[in]	x	x軸の要素
	 * @param[in]	y	y軸の要素
	 */
	Point(const TYPE& x,
		  const TYPE& y)
		: x_(x), y_(y)
		{
			;
		}

	/**
	 * ノルムの算出
	 * @return	ノルム
	 */
	TYPE
	norm() const
		{
			return x_ * x_ + y_ * y_;
		}

	/**
	 * ベクタとしての大きさ
	 * @return	大きさ
	 */
	TYPE
	abs() const
		{
			return (TYPE)std::sqrt(norm());
		}

	/**
	 * ベクタとしての和
	 * @param[in]	p	加算対象
	 * @return	和のベクトル
	 */
	Point<TYPE>
	operator + (const Point<TYPE>& p) const
		{
			return Point<TYPE>(x_ + p.x_, y_ + p.y_);
		}

	/**
	 * ベクタとしての差
	 * @param[in]	p	減算対象
	 * @return	差のベクトル
	 */
	Point<TYPE>
	operator - (const Point<TYPE>& p) const
		{
			return Point<TYPE>(x_ - p.x_, y_ - p.y_);
		}

	/**
	 * ベクタとしてのスカラー積
	 * @param[in]	k	スカラー
	 * @return	スカラー積のベクトル
	 */
	Point<TYPE>
	operator * (const TYPE& k) const
		{
			return Point<TYPE>(x_ * k, y_ * k);
		}

	/**
	 * ベクタの比較
	 * @param[in]	p	比較対象のベクタ
	 * @return	true: 左辺値が小さい, false: 左辺値が大きいか右辺値と等しい
	 * @note	書籍で記述があったため書いた。
	 */
	bool
	operator < (const Point<TYPE>& p) const
		{
			return x_ != p.x_ ? x_ < p.x_ : y_ < p.y_;
		}

	/**
	 * ベクタの比較
	 * @param[in]	p	比較対象のベクタ
	 * @return	true: 2つのベクタは等しい, false: 等しくない
	 * @note	誤差を考慮している。
	 */
	bool
	operator == (const Point<TYPE>& p) const
		{
			const TYPE EPS((TYPE)1.0E-10);

			if (EPS <= std::fabs(x_ - p.x_)) return false;
			if (EPS <= std::fabs(y_ - p.y_)) return false;
			return true;
		}

	/**
	 * 内積
	 * @param[in]	p	演算対象のベクタ
	 * @return	内積 (|a||b|cosΘ)
	 */
	TYPE
	dot_product(const Point<TYPE>& p) const
		{
			return x_ * p.x_ + y_ * p.y_;
		}

	/**
	 * 外積
	 * @param[in]	p	演算対象のベクタ
	 * @return	外積 (|a||b|sinΘ)
	 */
	TYPE
	cross_product(const Point<TYPE>& p) const
		{
			return x_ * p.y_ + y_ * p.x_;
		}
};

/// ベクタ
typedef	Point<double>	Vector;

/**
 * 2つのベクタが直交・並行かを確認
 * @param[in]	x1	1つめのベクタのx軸の要素
 * @param[in]	y1	1つめのベクタのy軸の要素
 * @param[in]	x2	2つめのベクタのx軸の要素
 * @param[in]	y2	2つめのベクタのy軸の要素
 * @return	1: 直交, 2: 並行, 0: それ以外
 */
int
check(double x1,
	  double y1,
	  double x2,
	  double y2)
{
	Vector p1(x1, y1);
	Vector p2(x2, y2);

	if (p1.dot_product(p2) == 0) return 1;		// 内積 == 0 => 直交
	if (p1.cross_product(p2) == 0) return 2;	// 外積 == 0 => 並行
	return 0;
}

#define	N	3

/**
 * サンプル・コマンド
 */
int
main()
{
	int lines[N][8] = {{0, 0, 3, 0, 0, 2, 3, 2},
					   {0, 0, 3, 0, 1, 1, 1, 4},
					   {0, 0, 3, 0, 1, 1, 2, 2}};

	for (int i(0); i < N; ++i) {
		std::printf("%d\n", check(lines[i][2] - lines[i][0],
								  lines[i][3] - lines[i][1],
								  lines[i][6] - lines[i][4],
								  lines[i][7] - lines[i][5]));
	}

	return 0;
}
