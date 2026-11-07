// 部品5 ConvertC のテスト（Claude が作成。このファイルは書き換えない）
//
// 動かし方（assembler フォルダで）:
//   clang++ -std=c++20 -Wall -Wextra -g -o test_ConvertC test_ConvertC.cpp && ./test_ConvertC
//
// 合格: 最後に「全部合格」と出る
//
// 前提: parts.h に次の関数がある
//   std::string ConvertC(std::string comp)
//   受け取る: splitDJC が切り出した comp の文字列（例 "M+1"）
//   返す:     7文字の "0" と "1"。先頭が a ビット（M を使うなら 1）、残り6文字が c ビット（本の図4-3）
//
// 本の表の28通りを全部確かめる。前半18個が a=0（A を使う・定数だけ）、後半10個が a=1（M を使う）

#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input, const std::string& expected)
{
    std::string actual = ConvertC(input);
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
    check("0",    "0101010");
    check("1",    "0111111");
    check("-1",   "0111010");
    check("D",    "0001100");
    check("A",    "0110000");
    check("!D",   "0001101");
    check("!A",   "0110001");
    check("-D",   "0001111");
    check("-A",   "0110011");
    check("D+1",  "0011111");
    check("A+1",  "0110111");
    check("D-1",  "0001110");
    check("A-1",  "0110010");
    check("D+A",  "0000010");
    check("D-A",  "0010011");
    check("A-D",  "0000111");
    check("D&A",  "0000000");
    check("D|A",  "0010101");
    check("M",    "1110000");
    check("!M",   "1110001");
    check("-M",   "1110011");
    check("M+1",  "1110111");
    check("M-1",  "1110010");
    check("D+M",  "1000010");
    check("D-M",  "1010011");
    check("M-D",  "1000111");
    check("D&M",  "1000000");
    check("D|M",  "1010101");

    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
