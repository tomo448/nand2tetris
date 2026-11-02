// 部品2 splitDJC のテスト（Claude が作成。このファイルは書き換えない）
//
// 動かし方（assembler フォルダで）:
//   clang++ -std=c++20 -Wall -Wextra -g -o test_splitDJC test_splitDJC.cpp && ./test_splitDJC
//
// 合格: 最後に「全部合格」と出る
//
// 前提: parts.h に次のものがある
//   struct CommandC { std::string comp; std::string dest; std::string jump; };
//   CommandC splitDJC(std::string c_command)
//   受け取る: コメントと空白を取り除いた C 命令の1行（例 "D=M+1"）
//   返す:     3つに切り分けた文字列。ない部分は空の文字列 ""（ビットにはしない。ビットにするのは ConvertD・ConvertJ）

#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input,
           const std::string& dest, const std::string& comp, const std::string& jump)
{
    CommandC c = splitDJC(input);
    if (c.dest == dest && c.comp == comp && c.jump == jump) {
        std::cout << "合格  " << input << '\n';
    } else {
        std::cout << "不合格 " << input << '\n'
                  << "    正しい: dest「" << dest   << "」 comp「" << comp   << "」 jump「" << jump   << "」\n"
                  << "    出力:   dest「" << c.dest << "」 comp「" << c.comp << "」 jump「" << c.jump << "」\n";
        ++failed;
    }
}

int main()
{
    //     入力            dest   comp    jump
    check("D=M+1",        "D",   "M+1",  "");     // jump がない
    check("M=D",          "M",   "D",    "");
    check("AMD=M-1",      "AMD", "M-1",  "");     // dest が3文字
    check("0;JMP",        "",    "0",    "JMP");  // dest がない。comp の "0" は意味のある記号
    check("D;JGT",        "",    "D",    "JGT");  // 電車の問い R-02
    check("D|M",          "",    "D|M",  "");     // dest も jump もない（comp だけ）
    check("M=!M",         "M",   "!M",   "");     // comp に記号
    check("AM=M+1;JEQ",   "AM",  "M+1",  "JEQ");  // 3つ全部ある

    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
