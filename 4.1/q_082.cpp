/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_082.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.82の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  逆ポーrンド記法は、
  演算子をオペランドの後に記述するプログラム (数式) を記述する記法です。
  例えば、一般的な中間記法で記述された (1+2)*(5+4) は、
  逆ポーランド記法では 1 2 + 5 4 + * と記述されます。
  逆ポーランド記法では、
  中間記法で必要とした括弧が不要である、というメリットがあります。

  逆ポーランド記法で与えられた数式の計算結果を出力してください。
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <stack>

/**
 * 逆ポーランド記法のトークン列を処理して数値を算出
 * @param[in]	tokens	トークン列
 * @param[in]	length	配列 @a tokens の要素数
 * @return	算出結果
 * @note	不正なトークン列に対する処理は不定。
 */
template<typename TYPE>
TYPE
calculate(const char** tokens,
		  size_t length)
{
	assert(tokens);
	assert(0 < length);

	TYPE l, r, n;
	std::stack<TYPE> stack;

	for (size_t i(0); i < length; ++i) {
		assert(tokens[i]);

		if (std::strcmp(tokens[i], "+") == 0) {
			r = stack.top();
			stack.pop();
			l = stack.top();
			stack.pop();
			stack.push(l + r);
			continue;
		}

		if (std::strcmp(tokens[i], "-") == 0) {
			r = stack.top();
			stack.pop();
			l = stack.top();
			stack.pop();
			stack.push(l - r);
			continue;
		}

		if (std::strcmp(tokens[i], "*") == 0) {
			r = stack.top();
			stack.pop();
			l = stack.top();
			stack.pop();
			stack.push(l * r);
			continue;
		}

		n = (TYPE)std::strtol(tokens[i], 0, 0);
		stack.push(n);
	}

	return stack.top();
}

#define	N	7

/**
 * サンプル・コマンド
 */
int
main()
{
	const char* tokens[N] = {"1", "2", "+", "3", "4", "-", "*"};

	std::printf("%d\n", calculate<int>(tokens, N));

	return 0;
}
