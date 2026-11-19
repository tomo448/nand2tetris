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

