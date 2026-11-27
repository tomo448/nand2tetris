#include"parts.h"
#include"fstream"
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>

std::vector<std::string> output1(const std::vector<std::string>& stream,const std::string& filename,CodeWriter& cw)
{
    Parser parser(stream);
    std::vector<std::string> output;
    //ofs<<"@256\n"<<"D=A\n"<<"@SP\n"<<"M=D\n";
    std::vector<std::string> op;
    cw.setFileName(filename);
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
        }
        for(auto& c:output)
            op.push_back(c);
    }
    return op;
}

int main(int argc,char* argv[])
{
    if(argc<1){
        std::cerr<<"ファイルを指定してください"<<std::endl;
        return 1;
    }
    std::vector<std::string> script;
    std::filesystem::path path=argv[1];
    std::vector<std::string> output;
    CodeWriter cw;
    if(std::filesystem::is_directory(path))
    {
        std::filesystem::path dirname=path.filename();
        path/=dirname;
        path.replace_extension(".asm");
        std::ofstream ofs(path);
        ofs<<"@256\n"<<"D=A\n"<<"@SP\n"<<"M=D\n";
        script.push_back("call Sys.init 0");
        output=output1(script,"",cw);
        for(auto& c:output)
        {
            ofs<<c<<std::endl;
        }
        for(const auto& dir_entry:std::filesystem::directory_iterator(argv[1]))
        {
            std::string filepath=dir_entry.path();
            std::string stem=std::filesystem::path(filepath).stem();
            std::string extension=std::filesystem::path(filepath).extension();
            if(extension==".vm")
            {
                std::ifstream ifs(filepath);
                script=PutInContainer(ifs);
                output=output1(script,stem,cw);
                for(auto& c:output)
                {
                    ofs<<c<<std::endl;
                }
            }
        }
        //std::string dirname=path.filename();
        
       
    }
    else
    {
        std::ifstream ifs(path);
        script=PutInContainer(ifs);
        path.replace_extension(".asm");
        std::ofstream ofs(path);
        output=output1(script,"",cw);
        for(auto& c:output)
        {
            ofs<<c<<std::endl;
        }
        //ofs<<"@256\n"<<"D=A\n"<<"@SP\n"<<"M=D\n";
    }
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
    /*Parser parser(script);
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
    }*/
    return 0;
}
