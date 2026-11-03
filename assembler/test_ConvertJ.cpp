// 部品4 ConvertJ のテスト
// 入力と正しい出力の8通りは、本人が記号の意味（<0・=0・>0）から組み立てて書いた（2026-11-04）。Claude が本の表と照らして確かめた
//
// 動かし方（assembler フォルダで）:
//   clang++ -std=c++20 -Wall -Wextra -g -o test_ConvertJ test_ConvertJ.cpp && ./test_ConvertJ
//
// 合格: 最後に「全部合格」と出る
//
// 前提: parts.h に次の関数がある
//   std::string ConvertJ(std::string jump)
//   受け取る: splitDJC が切り出した jump の文字列（ないときは空の文字列 ""）
//   返す:     3文字の "0" と "1"。左から <0・=0・>0 のときに飛ぶかどうか

#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input, const std::string& expected)
{
    std::string actual = ConvertJ(input);
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
    check("",    "000");  // jump がない（本の表の null）
    check("JGT", "001");  // >0
    check("JEQ", "010");  // =0
    check("JGE", "011");  // =0 か >0
    check("JLT", "100");  // <0
    check("JNE", "101");  // <0 か >0（文字とビットが対応しない例）
    check("JLE", "110");  // <0 か =0
    check("JMP", "111");  // いつでも

    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
