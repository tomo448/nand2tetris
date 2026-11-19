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
std::vector<std::string> inputFile(std::string src)
{
    std::ifstream ifs;
    std::vector<std::string> container;
    std::string line;
    ifs.open(src);
    if(!ifs.is_open())
    {
        std::cerr<<"ファイルが開けません"<<std::endl;
    }
    while(std::getline(ifs,line))
    {
        container.push_back(line);
    }
    return container;
}

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
    /*std::string line;
    std::vector<std::string> substr;
    std::stringstream ss(input);
    VMCommand vmc;
    while(std::getline(ss,line,' '))
    {
        substr.push_back(line);
    }
    for(int i=0;i<2;i++)
    {
        if(i==0)vmc.Command=substr[0];
        else if(i==1)vmc.arg1=substr[1];
        else vmc.arg2=substr[2];
    }*/
    std::vector<std::string> vs=SplitString(input);
    return CommandType::C_PUSH;
}

