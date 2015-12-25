/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_234.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.234の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  完全二分木で表された二分ヒープを読み込み、
  以下の形式で二分ヒープの各節点の情報を出力するプログラムを作成してください。

  node [id]: key = [k], parent key =[pk], left key = [lk], right key = [rk]

  ここで、[id] は節点の番号 (インデックス)、[k] は節点の値、
  [pk] は親の値、[lk] は左の子の値、[rk] は右のこの値を示します。
  これらの情報をこの順番で出力してください。
  ただし、該当する節点が存在しない場合は、出力を行わないものとします。
 */

/*
  メモ:
  - 書籍では1オリジンの表現をしているが、ここでは0オリジンで表現した。
  - 出力中の「, 」を、書籍に比べて極力出さないようにした。
 */

#include <cstdio>
#include <cassert>
#include <vector>

void
print(const std::vector<size_t> heap)
{
	for (size_t i(0); i < heap.size(); ++i) {
		std::printf("node %lu: key = %lu", i, heap[i]);
		if (0 < i) std::printf(", parent key = %lu", heap[(i-1)/2]);
		if (i * 2 + 1 < heap.size()) std::printf(", left key = %lu", heap[i*2+1]);
		if (i * 2 + 2 < heap.size()) std::printf(", right key = %lu", heap[i*2+2]);
		std::printf("\n");
	}
}

#define	N	5

int
main()
{
	std::vector<size_t> heap;
	heap.push_back(7);
	heap.push_back(8);
	heap.push_back(1);
	heap.push_back(2);
	heap.push_back(3);

	assert(heap.size() == N);

	print(heap);

	return 0;
}
