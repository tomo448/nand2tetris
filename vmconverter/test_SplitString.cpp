#include"parts.h"
#include<string>
#include<iostream>

int failed=0;

void check(const std::string& input,const std::vector<std::string>& expected)
{
    std::vector<std::string> actual=SplitString(input);
    if(actual==expected)
    {
        std::cout<<"合格"<<std::endl;
    }else{
        std::cout<<"不合格"<<std::endl;
        std::cout<<"出力:";
        for(size_t i=0;i!=actual.size();i++)
        {
            std::cout<<actual[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"正解:";
        for(size_t i=0;i!=expected.size();i++)
        {
            std::cout<<expected[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"出力文字数:"<<actual.size()<<std::endl;
        std::cout<<"正解文字数:"<<expected.size()<<std::endl;
        failed++;
    }
}

int main()
{
    check("add\r",{"add"});
    check("push that 5 ",{"push","that","5"});
    check("add",{"add"});
    check("push constant 7",{"push","constant","7"});
    check("    push     local   9    ",{"push","local","9"});
    if (failed==0) {
        std::cout<<"全部合格"<<std::endl;
    } else {
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
