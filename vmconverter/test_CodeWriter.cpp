#include"parts.h"
#include<iostream>
#include<string>
#include<vector>

int failed=0;

void checkAdd(CodeWriter& input,const std::vector<std::string>& expected)
{
    std::vector<std::string> actual=input.writeArithmetic();
    if(actual==expected)
    {
        std::cout<<"合格"<<std::endl;
    }
    else{
        std::cout<<"不合格"<<std::endl;
        std::cout<<"出力"<<std::endl;
        for(auto c:actual)
        {
            std::cout<<c<<std::endl;
        }
        std::cout<<"正解"<<std::endl;
        for(auto c:expected)
        {
            std::cout<<c<<std::endl;
        }
        failed++;
    }
}

void checkPush(CodeWriter& input,const std::vector<std::string>& expected)
{
    std::vector<std::string> actual=input.writePushPop();
    if(actual==expected)
    {
        std::cout<<"合格"<<std::endl;
    }
    else{
        std::cout<<"不合格"<<std::endl;
        std::cout<<"出力"<<std::endl;
        for(auto c:actual)
        {
            std::cout<<c<<std::endl;
        }
        std::cout<<"正解"<<std::endl;
        for(auto c:expected)
        {
            std::cout<<c<<std::endl;
        }
        failed++;
    }
}

int main()
{
    CodeWriter cw({"push constant 7","push constant 0","push constant 32767","add"});
    cw.next();
    checkPush(cw,{"@7","D=A","@SP","AM=M+1","A=A-1","M=D"});
    cw.next();
    checkPush(cw,{"@0","D=A","@SP","AM=M+1","A=A-1","M=D"});
    cw.next();
    checkPush(cw,{"@32767","D=A","@SP","AM=M+1","A=A-1","M=D"});
    cw.next();
    checkAdd(cw,{"@SP","AM=M-1","D=M","A=A-1","M=D+M"});
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
    }
    else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
