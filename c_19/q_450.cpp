/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_450.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.450の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  8クイーン問題とは、8x8のマスから成るチェス盤に、
  どのクイーンも他のクイーンを襲撃できないように、
  8つのクイーンを配置する問題です。
  チェスでは、
  クイーンは次のように (省略) 8方向のマスにいるコマを襲撃することができます。

  すでにクイーンが配置されているk個のマスが指定されるので、
  それらを合わせて8つのクイーンを配置したチェス盤を
  出力するプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <vector>

/**
 * N queens
 */
template<typename TYPE>
class NQueen
{
	size_t n_;	///< 盤の高さ・幅
	std::vector<size_t> j_;	///< 各行のクイーンの位置
	std::vector<TYPE> v_;	///< 各列の状態
	std::vector<TYPE> lu_;	///< 左上⇔右下の状態
	std::vector<TYPE> ru_;	///< 右上⇔左下の状態

public:

	/**
	 * コンストラクタ
	 * @param[in]	n	盤の高さ・幅
	 */
	NQueen(size_t n)
		: n_(n), j_(n, ~(size_t)0),
		  v_(n, 0), lu_(n*2, 0), ru_(n*2, 0)
		{
			assert(0 < n);
		}

	/**
	 * 指定の位置が既に利き筋か確認
	 * @param[in]	i	行
	 * @param[in]	j	列
	 * @return	true: 利き筋, false: 利き筋でない
	 */
	bool
	check(size_t i,
		  size_t j) const
		{
			assert(i < n_);
			assert(j < n_);

			bool r = j_[i] != ~(size_t)0;
			r |= v_[j];
			r |= lu_[n_-i+j];
			r |= ru_[i+j];

			return r;
		}

	/**
	 * 指定の位置にクイーンを配置
	 * @param[in]	i	行
	 * @param[in]	j	列
	 */
	void
	put(size_t i,
		size_t j)
		{
			assert(i < n_);
			assert(j < n_);
			assert(!check(i, j));

			j_[i] = j;
			v_[j] = lu_[n_-i+j] = ru_[i+j] = ~(TYPE)0;
		}

	/**
	 * 指定の位置からクイーンを除去
	 * @param[in]	i	行
	 * @param[in]	j	列
	 */
	void
	remove(size_t i,
		   size_t j)
		{
			assert(i < n_);
			assert(j < n_);
			assert(check(i, j));

			j_[i] = ~(size_t)0;
			v_[j] = lu_[n_-i+j] = ru_[i+j] = 0;
		}

	/**
	 * 解を1つ探索
	 * @param[in]	i	作業対象の行
	 * @return	true: 解があった, false: 解がなかった
	 */
	bool
	search(size_t i = 0)
		{
			if (n_ <= i) return true;

			if (j_[i] != ~(size_t)0) {
				return search(i+1);
			}
			else {
				bool f;

				for (size_t j(0); j < n_; ++j) {
					if (check(i, j)) continue;
					put(i, j);
					f = search(i+1);
					if (f) return true;
					remove(i, j);
				}
			}

			return false;
		}

	/**
	 * 盤を出力
	 * @param[in,out]	file	出力先
	 */
	void
	print(FILE* file = stdout) const
		{
			assert(file);

			for (size_t i(0); i < n_; ++i) {
				for (size_t j(0); j < n_; ++j) {
					std::fprintf(file, "%c", j_[i] == j ? 'Q' : '.');
				}
				std::fprintf(file, "\n");
			}
		}
};

#define	N	2

/**
 * サンプル・コマンド
 */
int
main()
{
	NQueen<char> nq(8);
	size_t command[N][2] = {{2, 2}, {5, 3}};

	for (int i(0); i < N; ++i) {
		nq.put(command[i][0], command[i][1]);
	}

	nq.search();

	nq.print();

	return 0;
}
