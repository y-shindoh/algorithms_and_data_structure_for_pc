/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_127.cpp
 * @brief	プログラミングコンテストのためのアルゴリズムとデータ構造p.127の問題の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839952957 .
 */

/*
  問題:
  以下の命令を実行する簡単な辞書を実装してください。
 */

/*
  メモ:
  テキストでは開番地法 (オープン・アドレス法) を用いているが、
  ここでは連鎖法 (チェイン法) を用いた。
 */

#include <cstdio>
#include <cassert>
#include <list>
#include <string>

/**
 * 簡単な辞書クラス
 * @note	リハッシュおよび削除処理は未実装。
 */
class Dictionary
{
private:

	std::list<std::string> table_[0x100];	///_ ハッシュテーブル

	/**
	 * ハッシュ関数もどき
	 * @param[in]	key	ハッシュ値を求める文字列
	 * @return	0〜255の整数
	 */
	static size_t
	hash(const char* key)
		{
			assert(key);

			unsigned char c(0);

			for (size_t i(0); key[i]; ++i) {
				c *= (unsigned char)key[i];
			}

			assert((size_t)c < 0x100);

			return (size_t)c;	// 余りを求めなくて良い
		}

public:

	/**
	 * 辞書内にキーがあるかを確認
	 * @param[in]	key	キー
	 * @return	true: あった, false: なかった
	 */
	bool
	find(const char* key)
		{
			assert(key);

			size_t k = Dictionary::hash(key);
			auto it = std::find(table_[k].begin(), table_[k].end(), std::string(key));
			return it != table_[k].end();
		}

	/**
	 * 辞書にキーを格納
	 * @param[in]	key	キー
	 * @note	既にキーが格納されている場合は何もしない。
	 */
	void
	insert(const char* key)
		{
			assert(key);

			if (find(key)) return;
			size_t k = Dictionary::hash(key);
			table_[k].push_back(std::string(key));
		}
};

/**
 * サンプル・コマンド
 */
int
main()
{
	Dictionary dictionary;

	dictionary.insert("AAA");
	dictionary.insert("AAC");
	std::printf("%s\n", dictionary.find("AAA") ? "yes" : "no");
	std::printf("%s\n", dictionary.find("CCC") ? "yes" : "no");
	dictionary.insert("CCC");
	dictionary.find("CCC");
	std::printf("%s\n", dictionary.find("CCC") ? "yes" : "no");

	return 0;
}
