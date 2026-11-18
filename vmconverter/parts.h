#include<iostream>
#include<vector>
#include<string>
#include<fstream>

enum class CommandType
{
    C_PUSH,
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

CommandType GetCommandType(const std::string& input)
{
    return CommandType::C_PUSH;
}
