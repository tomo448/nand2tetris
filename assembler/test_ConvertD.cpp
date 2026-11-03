// 部品3 ConvertD のテスト（Claude が作成。このファイルは書き換えない）
//
// 動かし方（assembler フォルダで）:
//   clang++ -std=c++20 -Wall -Wextra -g -o test_ConvertD test_ConvertD.cpp && ./test_ConvertD
//
// 合格: 最後に「全部合格」と出る
//
// 前提: parts.h に次の関数がある
//   std::string ConvertD(std::string dest)
//   受け取る: splitDJC が切り出した dest の文字列（ないときは空の文字列 ""）
//   返す:     3文字の "0" と "1"。左から A・D・M に書くかどうか（電車の問い 6-13）

#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input, const std::string& expected)
{
    std::string actual = ConvertD(input);
    if (actual == expected) {
        std::cout << "合格  「" << input << "」\n";
    } else {
        std::cout << "不合格 「" << input << "」\n"
                  << "    正しい: " << expected << " (" << expected.size() << "文字)\n"
                  << "    出力:   " << actual   << " (" << actual.size()   << "文字)\n";
        ++failed;
    }
}

int main()
{
    check("",    "000");  // dest がない（本の表の null）
    check("M",   "001");
    check("D",   "010");
    check("MD",  "011");
    check("A",   "100");
    check("AM",  "101");
    check("AD",  "110");
    check("AMD", "111");
    check("DM",  "011");  // 文字の順番が違う書き方（入れ替えた .asm にあった）。MD と同じビット

    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
