#include<iostream>
#include<string>
#include"parts.h"

int failed =0;

void check(const std::string& input,const std::string& expected)
{
    MapVar(input);
    std::string actual;
    actual=ConvertVar(input);
    if(expected==actual)
    {
        std::cout<<"　合格 「"<<input<<"」"<<std::endl;
    }else
    {
        std::cout<<"　不合格 「"<<input<<"」"<<std::endl;
        std::cout<<"正しい　："<<expected<<std::endl;
        std::cout<<"出力　："<<actual<<std::endl;
        failed++;
    }
}

int main()
{
    check("@i","16");
    check("@j","17");
    check("@i","16");
    check("@2","2");
    MapLabel("(LOOP)",13);
    check("@SCREEN","16384");
    check("@k","18");
    check("@R0","0");
    check("@LOOP","13");
    check("@l","19");
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
        return 0;
    }else
    {
        std::cout<<failed<<"件不合格"<<std::endl;
        return 1;
    }
}
