#include"parts.h"
#include"fstream"
#include<iostream>
#include<string>
#include<vector>

int main(int argc,char* argv[])
{
    if(argc<2){
        std::cerr<<"ファイルを指定してください"<<std::endl;
        return 1;
    }
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"入力用ファイルが開けません"<<std::endl;
        return 2;
    }
    std::ofstream ofs(argv[2]);
    if(!ofs.is_open())
    {
        std::cerr<<"出力用ファイルが開けません"<<std::endl;
        return 3;
    }
    std::vector<std::string> script;
    script=PutInContainer(ifs);
    Parser parser(script);
    std::vector<std::string> output;
    CodeWriter cw;
    while(parser.hasMoreCommands())
    {
        parser.advance();
        switch(parser.commandType())
        {
            case CommandType::C_PUSH:
                output=cw.writePushPop(parser.commandType(),parser.arg1(),parser.arg2());
                break;
            case CommandType::C_ARITHMETIC:
                output=cw.writeArithmetic(parser.arg1());
                break;
            default:
                std::cerr<<"コマンドが一致しません"<<std::endl;
                return 99;
        }
        for(auto& c:output)
            ofs<<c<<std::endl;
    }
    return 0;
}
