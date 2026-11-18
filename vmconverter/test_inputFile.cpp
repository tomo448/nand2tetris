#include"parts.h"
#include<string>
#include<iostream>
int failed =0;

std::string name(CommandType command)
{
    switch(command)
        case CommandType::C_PUSH: return "C_PUSH";
    return "?";
}
void check(const std::string& input,const CommandType expected)
{
    std::string actual=STR(GetCommandType(input));
    
    if(actual==expected)
        std::cout<<"合格"<<std::endl;
    else {
        std::cout<<"不合格"<<std::endl;
        std::cout<<"入力:"<<input<<"　出力:"<<actual<<"　正解:"<<expected<<std::endl;
        failed++;
    }
}

int main()
{
    check("push constant 7",CommandType::C_PUSH);
    check("pop local 2","C_POP");
    check("add","C_ARITHMETIC");
    check("neg","C_ARITHMETIC");
    
    if(failed==0)
        std::cout<<"全部合格"<<std::endl;
    else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
