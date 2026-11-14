#include<string>
#include<format>
#include<unordered_map>
#include<utility>
#include<cctype>
#include<algorithm>
#include<vector>
#include<fstream>
#include<iostream>

enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND };
int varAddress=15;

std::unordered_map<std::string,int> addressMap
{
    {"SP",0},{"R0",0},{"R1",1},{"R2",2},{"R3",3},{"R4",4},
    {"R5",5},{"R6",6},{"R7",7},{"R8",8},{"R9",9},
    {"R10",10},{"R11",11},{"R12",12},{"R13",13},{"R14",14},
    {"R15",15},{"SCREEN",16384},{"KBD",24576},{"LCL",1},
    {"ARG",2},{"THIS",3},{"THAT",4}
};

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

void MapLabel(const std::string& label,int address)
{
    std::string onlylabel=label.substr(1,label.length()-2);
    addressMap.insert(std::pair<std::string,int>{onlylabel,address});
}

bool is_number(const std::string& s) {
    if (s.empty()) return false;
    return std::all_of(s.begin(), s.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

void MapVar(const std::string& var)
{
    std::string onlyvar=var.substr(1,var.length()-1);
    if(is_number(onlyvar))return;
    if(addressMap.find(onlyvar)==addressMap.end())
    {
        varAddress++;
    }
    addressMap.insert(std::pair<std::string,int>{onlyvar,varAddress});
}

std::string ConvertVar(const std::string& input)
{
    std::string output;
    std::string onlyinput=input.substr(1,input.length()-1);
    if(is_number(onlyinput))
        output=onlyinput;
    else
        output=std::to_string(addressMap.at(onlyinput));
    return output;
}

std::vector<std::string> PutInContainer(std::ifstream& ifs)
{
    std::string line;
    std::string commentout("//");
    std::vector<std::string> container;
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
        if(result.empty())
            continue;
        container.push_back(result);
    }
    return container;
}

void FirstScan(const std::vector<std::string> input)
{
    int i=0;
    std::string parenthesis("(");
    for(const auto& v :input)
    {
        std::string::size_type pos=v.find(parenthesis);
        if(pos!=std::string::npos)
        {
            MapLabel(v,i);
            continue;
        }
        i++;
    }
}

std::vector<std::string> SecondScan(const std::vector<std::string>& input)
{
    std::string at("@");
    std::string result;
    std::string line;
    std::vector<std::string> output;
    for(const auto& v :input)
    {
        if(CommandType::A_COMMAND==JudgeAC(v))
        {
            std::string symbol=v.substr(1,v.length()-1);
            if(!addressMap.contains(symbol))
            {
                MapVar(v);
            }
            result=ConvertVar(v);
            result=at+result;
            line=ParserA(result);
        }
        else if(CommandType::C_COMMAND==JudgeAC(v))
        {
            line=ParserC(v);
        }else if(CommandType::L_COMMAND==JudgeAC(v))
        {
            continue;
        }
        output.push_back(line);
    }
    return output;
}
