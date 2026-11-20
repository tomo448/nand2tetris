#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdexcept>

enum class CommandType
{
    C_PUSH,C_ARITHMETIC,C_POP,C_LABEL,C_GOTO,C_IF,C_FUNCTION,C_RETURN,C_CALL
};

struct VMCommand
{
    std::string command;
    std::string arg1;
    std::string arg2;
};

enum class Segment
{
    LOCAL,ARGUMENT,THIS,THAT,POINTER,TEMP,CONSTANT,STATIC
};

const std::unordered_map<std::string,Segment> SegmentTable
{
    {"local",Segment::LOCAL},{"argument",Segment::ARGUMENT},{"this",Segment::THIS},{"that",Segment::THAT},{"pointer",Segment::POINTER},{"temp",Segment::TEMP},{"constant",Segment::CONSTANT},{"static",Segment::STATIC}
};

const std::unordered_map<std::string,CommandType> CommandTable
{
    {"push",CommandType::C_PUSH},{"pop",CommandType::C_POP},{"add",CommandType::C_ARITHMETIC},
    {"sub",CommandType::C_ARITHMETIC},{"neg",CommandType::C_ARITHMETIC},{"eq",CommandType::C_ARITHMETIC},
    {"gt",CommandType::C_ARITHMETIC},{"lt",CommandType::C_ARITHMETIC},{"and",CommandType::C_ARITHMETIC},{"or",CommandType::C_ARITHMETIC},{"not",CommandType::C_ARITHMETIC}
};

std::vector<std::string> SplitString(const std::string& input)
{
    std::string str;
    std::vector<std::string> vs;
    for(auto c:input)
    {
        if(!std::isspace(static_cast<unsigned char>(c)))
        {
            str+=c;
        }else{
            if(!str.empty())
                vs.push_back(str);
            str.clear();
        }
    }
    if(!str.empty())
        vs.push_back(str);
    return vs;
}

CommandType GetCommandType(const std::string& input)
{
    std::vector<std::string> vs=SplitString(input);
   if(vs.empty())
       throw std::invalid_argument("文字列が空です");
    std::string command=vs[0];
    if(!CommandTable.contains(command))
        throw std::out_of_range("そのようなコマンドはありません："+command);
    return CommandTable.at(command);
}

std::string GetArgument1(const std::vector<std::string>& input)
{
    std::string arg;
    if(GetCommandType(input[0])==CommandType::C_ARITHMETIC)
        arg=input[0];
    else
        arg=input[1];
    return arg;
}

int GetArgument2(const std::vector<std::string>& input)
{
    int arg=std::stoi(input[2]);
    return arg;
}

bool is_number(const std::string& str) {
    if (str.empty()) return false;
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

void CheckRightStyle(const std::vector<std::string>& input)
{
    int count=input.size();
    int rightcount=1;
    if(count==0) throw std::invalid_argument("命令列が空です");
    CommandType ct=GetCommandType(input[0]);
    if(ct==CommandType::C_POP||ct==CommandType::C_PUSH)
        rightcount=3;
    //命令コマンドの数が正しいかチェック
    if(rightcount!=count){
        if(rightcount>count)
            throw std::invalid_argument("命令形式が間違っています.命令の個数が"+std::to_string(rightcount-count)+"個少ないです");
        else
            throw std::invalid_argument("命令形式が間違っています.命令の個数が"+std::to_string(count-rightcount)+"個多いです");
    }else{//命令コマンドの数が正しい場合
        if(rightcount==3)
        {
            if(!SegmentTable.contains(input[1]))
                throw std::out_of_range("そのようなセグメントはありません："+input[1]);
            if(ct==CommandType::C_POP&&SegmentTable.at(input[1])==Segment::CONSTANT)
                throw std::out_of_range("popではconstantを使えません");
            if(!is_number(input[2]))
                throw std::invalid_argument("命令形式が間違っています．最後が数字でありません");
        }
    }
}
