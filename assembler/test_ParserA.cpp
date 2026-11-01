// 部品1 ParserA のテスト（Claude が作成。このファイルは書き換えない）
//
// 動かし方（assembler フォルダで）:
//   clang++ -std=c++20 -Wall -Wextra -g -o test_ParserA test_ParserA.cpp && ./test_ParserA
//
// 合格: 最後に「全部合格」と出る
//
// 前提: parts.h に次の関数がある
//   std::string ParserA(std::string a_command)
//   受け取る: コメントと空白を取り除いた A 命令の1行（例 "@2"）。@ の後ろは 0〜32767 の10進数
//   返す:     16文字の "0" と "1"（例 "0000000000000010"）

#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input, const std::string& expected)
{
    std::string actual = ParserA(input);
    if (actual == expected) {
        std::cout << "合格  " << input << '\n';
    } else {
        std::cout << "不合格 " << input << '\n'
                  << "    正しい: " << expected << " (" << expected.size() << "文字)\n"
                  << "    出力:   " << actual   << " (" << actual.size()   << "文字)\n";
        ++failed;
    }
}

int main()
{
    check("@2",     "0000000000000010");  // Add.asm の最初の行
    check("@0",     "0000000000000000");  // いちばん小さい数
    check("@21",    "0000000000010101");  // 電車の問い 6-10
    check("@16384", "0100000000000000");  // SCREEN の番地
    check("@24576", "0110000000000000");  // KBD の番地
    check("@32767", "0111111111111111");  // A 命令で書ける、いちばん大きい数

    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
