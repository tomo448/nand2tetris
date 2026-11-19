#include"parts.h"
#include<string>
#include<iostream>
#include<exception>
int failed =0;

std::string name(CommandType command)
{
    switch(command)
    {
        case CommandType::C_ARITHMETIC:return "C_ARITHMETIC";
        case CommandType::C_PUSH: return "C_PUSH";
        case CommandType::C_POP:return "C_POP";
        case CommandType::C_LABEL:return "C_LABEL";
        case CommandType::C_GOTO:return "C_GOTO";
        case CommandType::C_IF:return "C_IF";
        case CommandType::C_FUNCTION:return "C_FUNCTION";
        case CommandType::C_RETURN:return "C_RETURN";
        case CommandType::C_CALL:return "C_CALL";
    }
    return "?";
}
void check(const std::string& input,const CommandType expected)
{
   CommandType actual=GetCommandType(input);
    
    if(actual==expected)
        std::cout<<"合格"<<std::endl;
    else {
        std::cout<<"不合格"<<std::endl;
        std::cout<<"入力:"<<input<<"　出力:"<<name(actual)<<"　正解:"<<name(expected)<<std::endl;
        failed++;
    }
}

void checkException(const std::string& input)
{
    try {
        GetCommandType(input);
    } catch (std::exception& ex) {
        std::cerr<<ex.what()<<std::endl;
        return;
    }
    failed++;
}

int main()
{
    check("push constant 7",CommandType::C_PUSH);
    check("pop local 2",CommandType::C_POP);
    check("add",CommandType::C_ARITHMETIC);
    check("sub",CommandType::C_ARITHMETIC);
    check("neg",CommandType::C_ARITHMETIC);
    check("eq",CommandType::C_ARITHMETIC);
    check("gt",CommandType::C_ARITHMETIC);
    check("lt",CommandType::C_ARITHMETIC);
    check("and",CommandType::C_ARITHMETIC);
    check("or",CommandType::C_ARITHMETIC);
    check("not",CommandType::C_ARITHMETIC);
    checkException(" ");
    checkException("poi");
    if(failed==0)
        std::cout<<"全部合格"<<std::endl;
    else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
