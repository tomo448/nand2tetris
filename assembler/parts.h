#include<string>
#include<format>

std::string ParserA(const std::string a_command)
{
    //@を飛ばす．命令の判定は他の関数．ここにくるのはA命令でエラー判定しない
    std::string value =a_command.substr(1);
    int num=std::stoi(value);
    std::string binstr=std::format("{:016b}",num);
    return binstr;
}

struct CommandC{
    std::string comp;
    std::string dest;
    std::string jump;
};

CommandC splitDJC(std::string c_command)
{
    const std::string semicolon=";";
    const std::string equal="=";
    std::string comp,jump,dest;
    std::string::size_type pos1=c_command.find(semicolon);
    std::string::size_type pos2=c_command.find(equal);
    if(pos1!=std::string::npos)
    {  jump=c_command.substr(pos1+1);
        c_command=c_command.substr(0,pos1);
    }
    if(pos2!=std::string::npos)
    {   dest=c_command.substr(0,pos2);
        c_command=c_command.substr(pos2+1);
    }
    comp=c_command;
    return CommandC{comp,dest,jump};
}

std::string ConvertD(std::string dest)
{
    std::string d="000";
    if(dest.find("A")!=std::string::npos)
    {
        d.at(0)='1';
    }
    if(dest.find("D")!=std::string::npos)
    {
        d.at(1)='1';
    }
    if(dest.find("M")!=std::string::npos)
    {
        d.at(2)='1';
    }
    return d;
}
