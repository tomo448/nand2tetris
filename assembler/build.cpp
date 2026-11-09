#include"parts.h"
#include<iostream>
#include<fstream>
#include<string>

int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cout<<"読みたいファイルパスを入力して"<<std::endl;
    }
    
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"ファイルが開けませんでした"<<std::endl;
        return 1;
    }
    
    std::ofstream ofs(argv[2]);
    if(!ofs.is_open())
    {
        std::cerr<<"ファイルが開けませんでした"<<std::endl;
        return 1;
    }
    std::string line;
    std::string commentout("//");
    while(std::getline(ifs,line))
    {
        std::string::size_type pos=line.find(commentout);
        if(pos!=std::string::npos)
            line.erase(pos);
        
        std::string result;
        for(char c:line)
        {
            if(!std::isspace(static_cast<unsigned char>(c)))
                result +=c;
        }
        //line=result;
        if(result.empty())
            continue;
        if(CommandType::A_COMMAND==JudgeAC(result))
        {
            line=ParserA(result);
        }
        else if(CommandType::C_COMMAND==JudgeAC(result))
        {
            line=ParserC(result);
        }
        ofs<<line<<std::endl;
    }
    ofs.close();
    return 0;
}
