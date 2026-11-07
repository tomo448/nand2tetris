#include <iostream>
#include <string>
#include "parts.h"

int failed = 0;

void check(const std::string& input, const std::string& expected)
{
    std::string actual = ParserC(input);
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
    check("D=M+1","1111110111010000");
    check("M=D","1110001100001000");
    check("0;JMP","1110101010000111");
    check("D;JGT","1110001100000001");
    check("D|M", "1111010101000000");
    // ここから2つは Claude が足した（3つ全部ある・dest が3文字）
    check("AM=M+1;JEQ", "1111110111101010");
    check("AMD=D-1",    "1110001110111000");
    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
