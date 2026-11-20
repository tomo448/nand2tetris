#include<iostream>
#include<vector>
#include<string>
#include"parts.h"

int failed=0;

void check(const std::string& input,const std::string& expected1,int expected2)
{
    std::vector<std::string> actual=SplitString(input);
    std::string arg1=GetArgument1(actual);
    int arg2=GetArgument2(actual);
    if(arg1==expected1&&arg2==expected2)
    {
        std::cout<<"合格"<<" 入力:"<<input<<std::endl;
    }else
    {
        std::cout<<"不合格"<<" 入力:"<<input<<std::endl;
        std::cout<<"出力(引数1):"<<arg1<<" 正解(引数1):"<<expected1<<std::endl;
        std::cout<<"出力(引数2):"<<arg2<<" 正解(引数2):"<<expected2<<std::endl;
        failed++;
    }
}

void check(const std::string& input,const std::string& expected)
{
    std::vector<std::string> actual=SplitString(input);
    std::string arg1=GetArgument1(actual);
    if(arg1==expected)
    {
        std::cout<<"合格"<<" 入力:"<<input<<std::endl;
    }else
    {
        std::cout<<"不合格"<<" 入力:"<<input<<std::endl;
        std::cout<<"出力:"<<arg1<<" 正解:"<<expected<<std::endl;
        failed++;
    }
}

int main()
{
    check("push constant 7","constant",7);
    check("add","add");
    check("pop local 3","local",3);
    check("neg","neg");
    check("push temp 0","temp",0);
    check("push constant 32767","constant",32767);
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
    }else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
