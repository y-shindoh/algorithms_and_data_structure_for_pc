/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_240.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.240の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  優先度付きキュー (Priority Queue) は
  各要素がキーを持ったデータの集合Sを保持するデータ構造で、
  主に次の操作を行います。

  - insert(S, k): 集合Sに要素kを挿入する
  - extractMax(S): 最大のキーを持つSの要素をSから削除してその値を返す

  優先度付きキューSに対して
  insert(S, k), extractMax(S) を行うプログラムを作成してください。
  ここでは、
  キューの要素を整数とし、それ自身をキーとみなします。
 */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

/**
 * 指定位置の要素をmax-ヒープの性質に合うように上昇
 * @param[in,out]	heap	max-ヒープ
 * @param[in]	i	処理対象の要素の位置
 * @note	兄弟が処理済みの時に O(1) になることに注意。
 */
template<typename TYPE>
void
upheapify(std::vector<TYPE>& heap,
		  size_t i)
{
	assert(!heap.empty());
	assert(i < heap.size());

	size_t p, j;

	while (0 < i) {
		p = (i - 1) / 2;	// 親
		i = p * 2 + 1;		// 左の子
		j = p * 2 + 2;		// 右の子
		if (j < heap.size() && heap[i] < heap[j]) std::swap(i, j);
		if (heap[i] <= heap[p]) break;
		std::swap(heap[i], heap[p]);
		i = p;
	}
}

/**
 * 指定位置の要素をmax-ヒープの性質に合うように下降
 * @param[in,out]	heap	max-ヒープ
 * @param[in]	i	処理対象の要素の位置
 * @param[in]	n	配列 @a heap の要素数
 */
template<typename TYPE>
void
downheapify(std::vector<TYPE>& heap,
			size_t i)
{
	assert(!heap.empty());
	assert(i < heap.size());

	size_t j, k;

	while ('-') {
		j = i * 2 + 1;		// 左の子
		k = i * 2 + 2;		// 右の子
		if (heap.size() <= j) break;
		if (k < heap.size() && heap[j] < heap[k]) std::swap(j, k);
		if (heap[j] <= heap[i]) break;
		std::swap(heap[i], heap[j]);
		i = j;
	}
}

/**
 * max-ヒープに要素を追加
 * @param[in,out]	heap	max-ヒープ
 * @param[in]	value	追加する要素
 */
template<typename TYPE>
void
insert(std::vector<TYPE>& heap,
	   const TYPE& value)
{
	size_t i = heap.size();
	heap.push_back(value);
	upheapify<TYPE>(heap, i);
}

/**
 * max-ヒープから最大値を取得
 * @param[in,out]	heap	max-ヒープ
 * @return	取得した最大値
 */
template<typename TYPE>
TYPE
extract(std::vector<TYPE>& heap)
{
	assert(!heap.empty());

	TYPE value = heap.front();
	heap[0] = heap.back();
	heap.pop_back();
	if (!heap.empty()) downheapify<TYPE>(heap, 0);

	return value;
}

#define	N	10

/**
 * サンプル・コマンド
 */
int
main()
{
	int v;
	std::vector<int> h;

	insert(h, 8);
	insert(h, 2);
	std::printf("%d\n", extract(h));
	insert(h, 10);
	std::printf("%d\n", extract(h));
	insert(h, 11);
	std::printf("%d\n", extract(h));
	std::printf("%d\n", extract(h));

	return 0;
}
