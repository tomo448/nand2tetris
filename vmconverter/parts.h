#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

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
    return CommandType::C_PUSH;
}

