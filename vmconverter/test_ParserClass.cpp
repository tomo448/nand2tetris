#include"parts.h"
#include<string>
#include<vector>
#include<stdexcept>

int failed=0;

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

void check(Parser& input,const CommandType expected1,const std::string& expected2)
{
    CommandType command=input.commandType();
    std::string arg1=input.arg1();
    if(command==expected1&&arg1==expected2)
    {
        std::cout<<"合格"<<std::endl;
    }else
    {
        std::cout<<"不合格"<<std::endl;
        std::cout<<"出力:"<<name(command)<<" 正解:"<<name(expected1)<<std::endl;
        std::cout<<"出力:"<<arg1<<" 正解:"<<expected2<<std::endl;
        failed++;
    }
}

void check(Parser& input,const CommandType expected1,const std::string& expected2,int expected3)
{
    CommandType command=input.commandType();
    std::string arg1=input.arg1();
    int arg2=input.arg2();
    if(command==expected1&&arg1==expected2&&arg2==expected3)
    {
        std::cout<<"合格"<<std::endl;
    }else
    {
        std::cout<<"不合格"<<std::endl;
        std::cout<<"出力:"<<name(command)<<" 正解:"<<name(expected1)<<std::endl;
        std::cout<<"出力(引数1):"<<arg1<<" 正解(引数1):"<<expected2<<std::endl;
        std::cout<<"出力(引数2):"<<arg2<<" 正解(引数2):"<<expected3<<std::endl;
        failed++;
    }
}

void checkException(Parser& input)
{
    try {
        input.advance();
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
    Parser parser({"push constant 7","add","pop local 3"});
    parser.advance();
    check(parser,CommandType::C_PUSH,"constant",7);
    parser.advance();
    check(parser,CommandType::C_ARITHMETIC,"add");
    parser.advance();
    check(parser,CommandType::C_POP,"local",3);
    checkException(parser);
    Parser p2({});
    checkException(p2);
    if(failed==0)
        std::cout<<"全部合格"<<std::endl;
    else
        std::cout<<failed<<"件不合格"<<std::endl;
}
