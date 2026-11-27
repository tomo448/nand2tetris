#include"parts.h"
#include"fstream"
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>

int main(int argc,char* argv[])
{
    if(argc<1){
        std::cerr<<"ファイルを指定してください"<<std::endl;
        return 1;
    }
    std::vector<std::string> script;
    std::filesystem::path path=argv[1];
    if(std::filesystem::is_directory(path))
    {
        for(const auto& dir_entry:std::filesystem::directory_iterator(path))
        {
            std::string filepath=dir_entry.path();
            //std::string stem=std::filesystem::path(filepath).stem();
            std::string extension=std::filesystem::path(filepath).extension();
            if(extension==".vm")
            {
                std::ifstream ifs(filepath);
                PutInContainer(ifs,script);
            }
        }
        auto pos=script.begin();
        script.insert(pos,"call Sys.init 0");
        std::string dirname=path.filename();
        path.append(dirname);
        path.replace_extension(".asm");
    }
    else
    {
        std::ifstream ifs(path);
        PutInContainer(ifs,script);
        path.replace_extension(".asm");
    }
    std::ofstream ofs(path);
    /*if(!ifs.is_open())
    {
        std::cerr<<"入力用ファイルが開けません"<<std::endl;
        return 2;
    }*/
    /*if(!ofs.is_open())
    {
        std::cerr<<"出力用ファイルが開けません"<<std::endl;
        return 3;
    }*/
    Parser parser(script);
    std::vector<std::string> output;
    ofs<<"@256\n"<<"D=A\n"<<"@SP\n"<<"M=D\n";
    CodeWriter cw;
    while(parser.hasMoreCommands())
    {
        parser.advance();
        switch(parser.commandType())
        {
            case CommandType::C_PUSH:
                output=cw.writePushPop(parser.commandType(),parser.arg1(),parser.arg2());
                break;
            case CommandType::C_POP:
                output=cw.writePushPop(parser.commandType(),parser.arg1(),parser.arg2());
                break;
            case CommandType::C_ARITHMETIC:
                output=cw.writeArithmetic(parser.arg1());
                break;
            case CommandType::C_LABEL:
                output=cw.writeLabel(parser.arg1());
                break;
            case CommandType::C_GOTO:
                output=cw.writeGoto(parser.arg1());
                break;
            case CommandType::C_IF:
                output=cw.writeIf(parser.arg1());
                break;
            case CommandType::C_CALL:
                output=cw.writeCall(parser.arg1(),parser.arg2());
                break;
            case CommandType::C_FUNCTION:
                output=cw.writeFunction(parser.arg1(),parser.arg2());
                break;
            case CommandType::C_RETURN:
                output=cw.writeReturn();
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
