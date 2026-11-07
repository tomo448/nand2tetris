#include <iostream>
#include <string>
#include "parts.h"   // ここに enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND }; と JudgeAC がある

int failed = 0;

std::string name(CommandType t)   // 表示用
{
    switch (t) {
        case CommandType::A_COMMAND: return "A_COMMAND";
        case CommandType::C_COMMAND: return "C_COMMAND";
        case CommandType::L_COMMAND: return "L_COMMAND";
    }
    return "?";
}

void check(const std::string& input, CommandType expected)   // enum は小さいので値で渡す
{
    CommandType actual = JudgeAC(input);
    if (actual == expected) {
        std::cout << "合格  「" << input << "」\n";
    } else {
        std::cout << "不合格 「" << input << "」\n"
                  << "    正しい: " << name(expected) << "\n"
                  << "    出力:   " << name(actual)   << "\n";
        ++failed;
    }
}


int main()
{
    check("@12",CommandType::A_COMMAND);
    check("D=D-A",CommandType::C_COMMAND);
    check("@99",CommandType::A_COMMAND);
    check("0;JMP",CommandType::C_COMMAND);
    check("D;JGT",CommandType::C_COMMAND);
    check("(LOOP)",CommandType::L_COMMAND);
    check("D|M", CommandType::C_COMMAND);
    if (failed == 0) {
        std::cout << "全部合格\n";
        return 0;
    }
    std::cout << failed << " 件が不合格\n";
    return 1;
}
