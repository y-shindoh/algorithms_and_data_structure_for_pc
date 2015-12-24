/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_203.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.203の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  ある二分木に対して、
  それぞれ先行順巡回と中間順巡回を行って得られる節点の列が与えられるので、
  その二分木の後行順巡回で得られる節点の列を出力するプログラムを作成してください。
 */

/*
  メモ:
  - 書籍では1始まりのインデックスを用いているが、ここでは0始まりで実装している。
  - preorder 配列の参照位置の進め方で少し手間取った。
 */

#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 問題の回答
 * @param[in]	preorder	preorderのインデックスの配列
 * @param[in]	inorder	inorderのインデックスの配列
 * @param[out]	postorder	postorderのインデックスの配列
 * @param[in,out]	index	処理対象の @a preorder の位置
 * @param[in]	head	処理対象の @a inorder の先頭
 * @param[in]	tail	処理対象の @a inorder の末尾
 * @note	外部からの呼び出し時は @a index は @a preorder の先頭要素と等しい値にする。
 */
void
search(const size_t* preorder,
	   const size_t* inorder,
	   std::vector<size_t>& postorder,
	   size_t& index,
	   size_t head,
	   size_t tail)
{
	assert(preorder);
	assert(inorder);
	assert(head <= tail);

	size_t x = preorder[index];
	++index;	// preorderの参照対象の位置を1つ進める

	size_t h(~(size_t)0);	// 参照対象のinorder内での位置
	for (size_t i(head); i <= tail; ++i) {
		if (x != inorder[i]) continue;
		h = i;
		break;
	}
	assert(h != ~(size_t)0);

	// 左部分木
	if (head < h) search(preorder, inorder, postorder, index, head, h-1);

	// 右部分木
	if (h < tail) search(preorder, inorder, postorder, index, h+1, tail);

	// 参照要素
	postorder.push_back(x);
}

#define	N	5

/**
 * サンプル・コマンド
 */
int
main()
{
	const size_t preorder[N] = {0, 1, 2, 3, 4};
	const size_t inorder[N] =  {2, 1, 3, 0, 4};
	std::vector<size_t> postorder;
	size_t h(0);

	search(preorder, inorder, postorder, h, 0, N-1);

	for (int i(0); i < N; ++i) {
		if (0 < i) std::printf(" ");
		std::printf("%lu", postorder[i]);
	}
	std::printf("\n");

	return 0;
}
