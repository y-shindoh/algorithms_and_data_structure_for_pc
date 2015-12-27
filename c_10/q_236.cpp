/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_236.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.236の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  与えられた配列から以下の擬似コード (省略) に従って
  max-ヒープを構築するプログラムを作成してください。

  maxHeapify(A, i) は、節点iを根とする部分木がmax-ヒープになるよう
  A[i] の値をmax-ヒープの葉へ向かって降下させます。
  ここでHをヒープサイズとします。

  次の buildMaxHeap(A) (省略) は
  ボトムアップに maxHeapify を適用することで配列Aをmax-ヒープに変換します。
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

/**
 * 指定位置の要素をmax-ヒープの性質に合うように下降
 * @param[in,out]	heap	max-ヒープ
 * @param[in]	i	処理対象の要素の位置
 * @param[in]	n	配列 @a heap の要素数
 */
template<typename TYPE>
void
downheapify(TYPE* heap,
			size_t i,
			size_t n)
{
	assert(heap);
	assert(0 < n);
	assert(i < n);

	size_t j, k;

	while ('-') {
		j = i * 2 + 1;		// 左の子
		k = i * 2 + 2;		// 右の子
		if (n <= j) break;
		if (k < n && heap[j] < heap[k]) std::swap(j, k);
		if (heap[j] <= heap[i]) break;
		std::swap(heap[i], heap[j]);
		i = j;
	}
}

/**
 * 配列をmax-ヒープに変換
 * @param[in,out]	heap	処理対象の配列
 * @param[in]	n	配列 @a heap の要素数
 */
template<typename TYPE>
void
build_heap(TYPE* heap,
		   size_t n)
{
	assert(heap);

	for (size_t i(n/2); 0 < i; --i) {
		downheapify<TYPE>(heap, i - 1, n);
	}
}

#define	N	10

/**
 * サンプル・コマンド
 */
int
main()
{
	int a[N] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

	build_heap(a, N);

	std::for_each(a, a + N, [](int x) { std::printf(" %d", x); });
	std::printf("\n");

	return 0;
}
