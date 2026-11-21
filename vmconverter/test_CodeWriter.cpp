#include"parts.h"
#include<iostream>
#include<string>
#include<vector>

int failed=0;

void checkArithmetic(CodeWriter& input,const std::string& command,const std::vector<std::string>& expected)
{
    std::vector<std::string> actual=input.writeArithmetic(command);
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

void checkPushPop(CodeWriter& input,CommandType command ,const std::string& arg1,int arg2,const std::vector<std::string>& expected)
{
    std::vector<std::string> actual=input.writePushPop(command,arg1,arg2);
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

void checkExceptionArithmetic(CodeWriter& input,const std::string& command)
{
    try {
        std::vector<std::string> actual=input.writeArithmetic(command);
    } catch (std::exception& e) {
        std::cout<<"合格"<<std::endl;
        std::cerr<<e.what()<<std::endl;
        return;
    }
    std::cout<<"不合格"<<std::endl;
    failed++;
}

void checkExceptionPushPop(CodeWriter& input,CommandType command,const std::string& arg1,int arg2)
{
    try {
        std::vector<std::string> actual=input.writePushPop(command,arg1,arg2);
    } catch (std::exception& e) {
        std::cout<<"合格"<<std::endl;
        std::cerr<<e.what()<<std::endl;
        return;
    }
    std::cout<<"不合格"<<std::endl;
    failed++;
}

int main()
{
    Parser parser({"push constant 7","push constant 0","push constant 32767","add","push local 2","neg","gt","lt"});
    CodeWriter cw;
    checkPushPop(cw,CommandType::C_PUSH,"constant",7,{"@7","D=A","@SP","AM=M+1","A=A-1","M=D"});
    checkPushPop(cw,CommandType::C_PUSH,"constant",0,{"@0","D=A","@SP","AM=M+1","A=A-1","M=D"});
    checkPushPop(cw,CommandType::C_PUSH,"constant",32767,{"@32767","D=A","@SP","AM=M+1","A=A-1","M=D"});
    checkArithmetic(cw,"add",{"@SP","AM=M-1","D=M","A=A-1","M=D+M"});
    checkExceptionPushPop(cw,CommandType::C_PUSH,"local",2);
    checkExceptionArithmetic(cw,"neg");
    checkExceptionArithmetic(cw,"gt");
    checkExceptionArithmetic(cw,"lt");
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
    }
    else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
