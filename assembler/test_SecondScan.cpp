#include"parts.h"
#include<iostream>
#include<string>
#include<vector>

int failed=0;

// 1行ずつ比べる。ずれた行の番号と、入力・正解・出力を見せる
void checkLines(const std::vector<std::string>& actual,
                const std::vector<std::string>& expected)
{
    if(actual.size()!=expected.size())
    {
        std::cout<<"不合格: 行の数がちがう（正解 "<<expected.size()
                 <<" 行 / 出力 "<<actual.size()<<" 行）\n";
        ++failed;
        return;
    }
    for(std::size_t i=0;i<expected.size();++i)
    {
        if(actual[i]!=expected[i])
        {
            std::cout<<"不合格 "<<i<<" 行目\n"
                     <<"　正解: "<<expected[i]<<"\n"
                     <<"　出力: "<<actual[i]<<"\n";
            ++failed;
        }
    }
}

int main()
{
    // 前提を用意する: ラベルは、1回目の走査の代わりに自分で入れておく
    MapLabel("(LOOP)",3);

    // 入力: PutInContainer のあとの形（コメントと空白はもうない）
    std::vector<std::string> input{
        "D=M",
        "@2",
        "(LOOP)",   // 書き出さない
        "@LOOP",
        "@R0",
        "@SCREEN",
        "@i",
        "@j",
        "@i"
        // 段階Cで足す: "@R0", "@SCREEN", "@i", "@j", "@i"
    };

    // 正解: 16桁を4桁ずつ区切って、10進数に戻して確かめてから書く
    std::vector<std::string> expected{
        "1111110000010000",   // D=M
        "0000000000000010",   // @2
        "0000000000000011",   // @LOOP → 3
        "0000000000000000",
        "0100000000000000",
        "0000000000010000",
        "0000000000010001",
        "0000000000010000"
        // 段階Cで、自分で足す
    };

    std::vector<std::string> actual=SecondScan(input);
    checkLines(actual,expected);

    if(failed==0){ std::cout<<"全部合格\n"; return 0; }
    std::cout<<failed<<" 件が不合格\n";
    return 1;
}
