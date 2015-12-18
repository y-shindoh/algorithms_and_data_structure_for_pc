/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_087.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.87の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  名前 name_i と必要な処理時間 time_i を持つn個のプロセスが順番に一列に並んでいます。
  ラウンドロビンスケジューリングと呼ばれる処理方法では、
  CPUがプロセスを順番に処理します。
  各プロセスは最大q ms (これをクオンタムと呼びます) だけ処理が実行されます。
  q msだけ処理を行っても、まだそのプロセスが完了していなければ、
  そのプロセスは列の最後尾に移動し、CPUは次のプロセスに割り当てられます。

  例えば、q を 100 とし、以下のようなプロセスの列を考えます。

  A(150) - B(80) - C(200) - D(200)

  まずプロセスAが100msだけ処理され、
  残りの必要時間50msを保持し列の末尾に移動します。

  B(80) - C(200) - D(200) - A(50)

  次にプロセスBが80msだけ処理され、時刻180msで終了し、列から削除されます。

  C(200) - D(200) - A(50)

  次にプロセスCが100msだけ処理され、
  残りの必要時間100msを保持し列の末尾に移動します。

  D(200) - A(50) - C(100)

  このように、全てのプロセスが終了するまで処理を繰り返します。
  ラウンドロビンスケジューリングをシミュレートするプログラムを作成してください。
 */

#include <cstdio>
#include <cassert>
#include <queue>
#include <algorithm>

/**
 * ラウンドロビンスケジューリングのシミュレータ
 * @param[in]	names	タスク名の配列
 * @param[in,out]	times	タスクの必要処理時間の配列 (全要素は0以上)
 * @param[in]	length	配列 @a names, @a times の要素数
 * @param[in]	クオンタム
 * @note	処理終了後に @a times の全要素は 0 になる。
 */
template<typename TYPE>
void
roundrobin_simulator(const char** names,
					 TYPE* times,
					 size_t length,
					 TYPE quantum)
{
	assert(names);
	assert(times);
	assert(0 < quantum);

	std::queue<size_t> queue;
	TYPE total(0);
	TYPE done;
	size_t h;

	for (size_t i(0); i < length; ++i) {
		assert(names[i]);
		assert(0 <= times[i]);
		queue.push(i);
	}

	while (0 < queue.size()) {
		h = queue.front();
		queue.pop();
		done = std::min(times[h], quantum);
		total += done;
		times[h] -= done;

		if (0 < times[h]) {
			// 処理継続
			queue.push(h);
		}
		else {
			// 処理完了 (終了時間を出力)
			std::printf("%s %G\n", names[h], (double)total);
		}
	}
}

#define	N	5
#define	Q	100

/**
 * サンプル・コマンド
 */
int
main(void)
{
	const char* names[N];
	int times[N] = {150, 80, 200, 350, 20};

	names[0] = "p1";
	names[1] = "p2";
	names[2] = "p3";
	names[3] = "p4";
	names[4] = "p5";

	roundrobin_simulator(names, times, N, Q);

	return 0;
}
