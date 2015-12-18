/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_095.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.95の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  以下の命令を受け付ける双方向連結リストを実装してください。

  - insert x: 連結リストの先頭にキーxを持つ要素を継ぎ足す
  - delete x: キーxを持つ最初の要素を連結リストから削除する
  - deleteFirst: 連結リストの先頭の要素を削除する
  - deleteLast: 連結リストの末尾の要素を削除する
 */

#include <cstdio>

/**
 * 双方向連結リストのノード
 */
template<typename TYPE>
class Node
{
public:
	TYPE d_;		///< データ
	Node<TYPE>* p_;	///< 前のノード
	Node<TYPE>* n_;	///< 次のノード

	/**
	 * コンストラクタ
	 * @param[in]	d	保持するデータ
	 */
	Node(const TYPE& d)
		: d_(d), p_(0), n_(0)
		{
			;
		}
};

/**
 * 双方向連結リストにデータを追加
 * @param[in,out]	h	リストの先頭
 * @param[in]	d	追加するデータ
 * @return	処理後のリストの先頭
 */
template<typename TYPE>
Node<TYPE>*
insert(Node<TYPE>* h,
	   const TYPE& d)
{
	Node<TYPE>* n = new Node<TYPE>(d);

	if (h) h->p_ = n;
	n->n_ = h;

	return n;
}

/**
 * 双方向連結リストからデータを削除
 * @param[in,out]	h	リストの先頭
 * @param[in]	d	削除するデータ
 * @return	処理後のリストの先頭
 */
template<typename TYPE>
Node<TYPE>*
delete_find(Node<TYPE>* h,
			const TYPE& d)
{
	Node<TYPE>* n(h);

	while (h) {
		if (h->d_ == d) {
			if (h->p_) h->p_->n_ = h->n_;
			if (h->n_) h->n_->p_ = h->p_;
			if (h == n) n = h->n_;
			delete h;
			return n;
		}
		h = h->n_;
	}

	return h;
}

/**
 * 双方向連結リストの先頭のノードを削除
 * @param[in,out]	h	リストの先頭
 * @return	処理後のリストの先頭
 */
template<typename TYPE>
Node<TYPE>*
delete_first(Node<TYPE>* h)
{
	Node<TYPE>* n(0);

	if (h) n = h->n_;
	delete h;

	return n;
}

/**
 * 双方向連結リストの末尾のノードを削除
 * @param[in,out]	h	リストの先頭
 * @return	処理後のリストの先頭
 * @note	本来は末尾を指すポインタを直接処理すべきだが、ここではしない。
 */
template<typename TYPE>
Node<TYPE>*
delete_last(Node<TYPE>* h)
{
	if (!h) return 0;

	Node<TYPE>* n(h);
	while (h->n_) h = h->n_;

	if (n == h) {
		// 先頭
		delete h;
		return 0;
	}
	else {
		// 先頭以外
		h->p_->n_ = h->n_;
		if (h->n_) h->n_->p_ = h->p_;
		delete h;
		return n;
	}
}

/**
 * 双方向連結リストの要素を標準出力に書き出し
 * @param[in,out]	h	リストの先頭
 */
template<typename TYPE>
void
print(Node<TYPE>* h)
{
	bool body(false);

	while (h) {
		if (body) std::printf(" ");
		body = true;
		std::printf("%G", (double)h->d_);
		h = h->n_;
	}
	std::printf("\n");
}

/**
 * サンプル・コマンド
 */
int
main()
{
	Node<int>* h(0);

	h = insert(h, 5);
	h = insert(h, 2);
	h = insert(h, 3);
	h = insert(h, 1);
	h = delete_find(h, 3);
	h = insert(h, 6);
	h = delete_find(h, 5);

	print(h);

	while (h) {
		h = delete_first(h);
		h = delete_last(h);
	}

	return 0;
}
