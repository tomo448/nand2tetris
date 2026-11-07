#include<string>
#include<format>
#include<unordered_map>

enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND };

const std::unordered_map<std::string,std::string> table
{
    {"0","101010"},{"1","111111"},{"-1","111010"},
    {"D","001100"},{"A","110000"},{"!D","001101"},
    {"!A","110001"},{"-D","001111"},{"-A","110011"},
    {"D+1","011111"},{"A+1","110111"},{"D-1","001110"},
    {"A-1","110010"},{"D+A","000010"},{"D-A","010011"},
    {"A-D","000111"},{"D&A","000000"},{"D|A","010101"}
};

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

std::string ConvertJ(std::string jump)
{
    std::string j="";
       if(jump== "")
            j="000";
        if(jump=="JGT")
            j="001";
        if(jump=="JEQ")
            j="010";
        if(jump=="JGE")
            j="011";
        if(jump=="JLT")
            j="100";
        if(jump=="JNE")
            j="101";
        if(jump=="JLE")
            j="110";
        if(jump=="JMP")
            j="111";
    return j;
}

std::string ConvertC(std::string comp)
{
    std::string c="0";
    std::string::size_type pos=comp.find("M");
    if(pos !=std::string::npos)
    {
        c.at(0)='1';
        comp.replace(pos,1,"A");
    }
    c.insert(1,table.at(comp));
    return c;
}

CommandType JudgeAC(std::string command)
{
    if(command[0]=='@')
    {
        return CommandType::A_COMMAND;
    }
    else if(command.find("(")!=std::string::npos)
    {
        return CommandType::L_COMMAND;
    }
    else
    {
        return CommandType::C_COMMAND;
    }
}

std::string ParserC(std::string c_command)
{
    std::string c="111";
    CommandC cmdc=splitDJC(c_command);
    c.insert(3,ConvertC(cmdc.comp));
    c.insert(10,ConvertD(cmdc.dest));
    c.insert(13,ConvertJ(cmdc.jump));
    return c;
}
