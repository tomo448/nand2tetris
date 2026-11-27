#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdexcept>

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

enum class Segment
{
    LOCAL,ARGUMENT,THIS,THAT,POINTER,TEMP,CONSTANT,STATIC
};

const std::unordered_map<std::string,Segment> SegmentTable
{
    {"local",Segment::LOCAL},{"argument",Segment::ARGUMENT},{"this",Segment::THIS},{"that",Segment::THAT},{"pointer",Segment::POINTER},{"temp",Segment::TEMP},{"constant",Segment::CONSTANT},{"static",Segment::STATIC}
};

const std::unordered_map<std::string,CommandType> CommandTable
{
    {"push",CommandType::C_PUSH},{"pop",CommandType::C_POP},{"add",CommandType::C_ARITHMETIC},
    {"sub",CommandType::C_ARITHMETIC},{"neg",CommandType::C_ARITHMETIC},{"eq",CommandType::C_ARITHMETIC},
    {"gt",CommandType::C_ARITHMETIC},{"lt",CommandType::C_ARITHMETIC},{"and",CommandType::C_ARITHMETIC},{"or",CommandType::C_ARITHMETIC},{"not",CommandType::C_ARITHMETIC},{"label",CommandType::C_LABEL},{"goto",CommandType::C_GOTO},{"if-goto",CommandType::C_IF},{"function",CommandType::C_FUNCTION},{"return",CommandType::C_RETURN},{"call",CommandType::C_CALL}
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
   if(vs.empty())
       throw std::invalid_argument("文字列が空です");
    std::string command=vs[0];
    if(!CommandTable.contains(command))
        throw std::out_of_range("そのようなコマンドはありません："+command);
    return CommandTable.at(command);
}

CommandType GetCommandType2(const std::vector<std::string>& input)
{
   if(input.empty())
       throw std::invalid_argument("文字列が空です");
    std::string command=input[0];
    if(!CommandTable.contains(command))
        throw std::out_of_range("そのようなコマンドはありません："+command);
    return CommandTable.at(command);
}

std::string GetArgument1(const std::vector<std::string>& input)
{
    std::string arg;
    if(GetCommandType(input[0])==CommandType::C_ARITHMETIC)
        arg=input[0];
    else
        arg=input[1];
    return arg;
}

int GetArgument2(const std::vector<std::string>& input)
{
    int arg=std::stoi(input[2]);
    return arg;
}

bool is_number(const std::string& str) {
    if (str.empty()) return false;
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

void CheckRightStyle(const std::vector<std::string>& input)
{
    int count=input.size();
    int rightcount=1;
    if(count==0) throw std::invalid_argument("命令列が空です");
    CommandType ct=GetCommandType(input[0]);
    bool hasArgument=ct==CommandType::C_POP||ct==CommandType::C_PUSH;
    if(hasArgument)
        rightcount=3;
    //命令コマンドの数が正しいかチェック
    if(rightcount!=count){
        if(rightcount>count)
            throw std::invalid_argument("命令形式が間違っています.言葉の個数が"+std::to_string(rightcount-count)+"個少ないです");
        else
            throw std::invalid_argument("命令形式が間違っています.言葉の個数が"+std::to_string(count-rightcount)+"個多いです");
    }
    //命令コマンドの数が正しい場合
    if(!hasArgument)return;
    if(!SegmentTable.contains(input[1]))
        throw std::out_of_range("そのようなセグメントはありません："+input[1]);
    if(ct==CommandType::C_POP&&SegmentTable.at(input[1])==Segment::CONSTANT)
        throw std::out_of_range("popではconstantを使えません");
    if(!is_number(input[2]))
        throw std::invalid_argument("命令形式が間違っています．最後が数字でありません");
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
        
        if(line.find_first_not_of(" \t\r\n") != std::string::npos)
        {
            pos=line.find_last_not_of(' ');
            if(pos!=std::string::npos)
            {
                line=line.substr(0,pos+1);
            }
            container.push_back(line);
        }
    }
    return container;
}

class Parser
{
public:
    Parser(std::vector<std::string> str){_str=str;_number_of_lines=-1;}
    bool hasMoreCommands(){int commandcount=_str.size();if(commandcount>(_number_of_lines+1))return true;return false;}
    void advance(){if(hasMoreCommands()){_number_of_lines++;_line=SplitString(_str[_number_of_lines]);}else{throw std::out_of_range("最後の行です");}}
    CommandType commandType(){return GetCommandType2(_line);}
    std::string arg1(){return GetArgument1(_line);}
    int arg2(){return GetArgument2(_line);}
    
private:
    std::vector<std::string> _str;
    std::vector<std::string> _line;
    int _number_of_lines;
};

class CodeWriter
{
public:
    CodeWriter(){}
    void setFileName(const std::string& filename)
    {
        _currentfilename=filename;
    }
    std::vector<std::string> writeArithmetic(const std::string& command)
    {
        if(command=="add")
            return writeAdd();
        else if(command=="sub")
            return writeSub();
        else if(command=="neg")
            return writeNeg();
        else if(command=="eq")
            return writeEqual();
        else if(command=="gt")
            return writeGreaterThan();
        else if(command=="lt")
            return writeLessThan();
        else if(command=="and")
            return writeAnd();
        else if(command=="or")
            return writeOr();
        else if(command=="not")
            return writeNot();
        else
            throw std::invalid_argument(command+"命令は未実装です");
    }
    std::vector<std::string> writePushPop(CommandType command,const std::string& arg1,int arg2)
    {
        if(command==CommandType::C_PUSH)
        {
            if(arg1=="constant")
            return {'@'+std::to_string(arg2),"D=A","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="local")
                return {"@LCL","D=M",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="argument")
                return {"@ARG","D=M",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="this")
                return {"@THIS","D=M",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="that")
                return {"@THAT","D=M",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="temp")
                return {"@5","D=A",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="pointer")
                return {"@3","D=A",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
            else if(arg1=="static")
                return {"@16","D=A",'@'+std::to_string(arg2),"A=D+A","D=M","@SP","AM=M+1","A=A-1","M=D"};
        }
        else if(command==CommandType::C_POP)
        {
            if(arg1=="local")
                return {"@SP","AM=M-1","D=M","@LCL","D=D+M",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="argument")
                return {"@SP","AM=M-1","D=M","@ARG","D=D+M",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="this")
                return {"@SP","AM=M-1","D=M","@THIS","D=D+M",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="that")
                return {"@SP","AM=M-1","D=M","@THAT","D=D+M",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="temp")
                return {"@SP","AM=M-1","D=M","@5","D=D+A",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="pointer")
                return {"@SP","AM=M-1","D=M","@3","D=D+A",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
            else if(arg1=="static")
                return {"@SP","AM=M-1","D=M","@16","D=D+A",'@'+std::to_string(arg2),"D=D+A","@SP","A=M","A=M","A=D-A","M=D-A"};
        }
            throw std::invalid_argument("popは未実装です");
    }
    std::vector<std::string> writeLabel(const std::string& arg1)
    {
        return {'('+arg1+')'};
    }
    std::vector<std::string> writeGoto(const std::string& arg1)
    {
        return {'@'+arg1,"0;JMP"};
    }
    std::vector<std::string> writeIf(const std::string& arg1)
    {
        return {"@SP","AM=M-1","D=M",'@'+arg1,"D;JNE"};
    }
    
    std::vector<std::string> writeCall(const std::string& funcname,int n)
    {
        std::string raddress=funcname+'$'+"return-address";
        return {'@'+raddress,"D=A","@SP","AM=M+1","A=A-1","M=D","@LCL","D=M","@SP","AM=M+1","A=A-1","M=D","@ARG","D=M","@SP","AM=M+1","A=A-1","M=D","@THIS","D=M","@SP","AM=M+1","A=A-1","M=D","@THAT","D=M","@SP","AM=M+1","A=A-1","M=D","@SP","D=M",'@'+std::to_string(n),"D=D-A","@5","D=D-A","@ARG","M=D","@SP","D=M","@LCL","M=D",'@'+funcname,"0;JMP",'('+raddress+')'};
    }
    std::vector<std::string> writeReturn()
    {
        return {"@LCL","D=M","@R13","M=D","@5","A=D-A","D=M","@R14","M=D","@SP","A=M-1","D=M","@ARG","A=M","M=D","@ARG","D=M","@SP","M=D+1","@R13","AM=M-1","D=M","@THAT","M=D","@R13","AM=M-1","D=M","@THIS","M=D","@R13","AM=M-1","D=M","@ARG","M=D","@R13","AM=M-1","D=M","@LCL","M=D","@R14","A=M","0;JMP"};
    }
    
    std::vector<std::string> writeFunction(const std::string& funcname,int k)
    {
        std::string funcstart=funcname+'$'+"FUNCLOOP";
        std::string funcend=funcname+'$'+"FUNCEND";
        return {'('+funcname+')',"@R13","M=1",'('+funcstart+')',"@R13","D=M",'@'+std::to_string(k),"D=D-A",'@'+funcend,"D;JGT","@SP","AM=M+1","A=A-1","M=0","@R13","M=M+1",'@'+funcstart,"0;JMP",'('+funcend+')'};
    }
private:
    std::string _currentfilename;
    int counts=0;
    std::vector<std::string> writeAdd()
    {
        return {"@SP","AM=M-1","D=M","A=A-1","M=D+M"};
    }
    std::vector<std::string> writeSub()
    {
        return {"@SP","AM=M-1","D=M","A=A-1","M=M-D"};
    }
    std::vector<std::string> writeEqual()
    {
        counts++;
        return {"@SP",
            "AM=M-1",
            "D=M",
            "A=A-1",
            "D=M-D",
            "@EQUAL"+std::to_string(counts),
            "D;JEQ",
            "@SP",
            "A=M-1",
            "M=0",
            "@END"+std::to_string(counts),
            "0;JMP",
            "(EQUAL"+std::to_string(counts)+")",
            "@SP",
            "A=M-1",
            "M=-1",
            "(END"+std::to_string(counts)+")"};
    }
    std::vector<std::string> writeLessThan()
    {
        counts++;
        return {"@SP",
            "AM=M-1",
            "D=M",
            "A=A-1",
            "D=M-D",
            "@LT"+std::to_string(counts),
            "D;JLT",
            "@SP",
            "A=M-1",
            "M=0",
            "@END"+std::to_string(counts),
            "0;JMP",
            "(LT"+std::to_string(counts)+")",
            "@SP",
            "A=M-1",
            "M=-1",
            "(END"+std::to_string(counts)+")"};
    }
    std::vector<std::string> writeGreaterThan()
    {
        counts++;
        return {"@SP",
            "AM=M-1",
            "D=M",
            "A=A-1",
            "D=M-D",
            "@GT"+std::to_string(counts),
            "D;JGT",
            "@SP",
            "A=M-1",
            "M=0",
            "@END"+std::to_string(counts),
            "0;JMP",
            "(GT"+std::to_string(counts)+")",
            "@SP",
            "A=M-1",
            "M=-1",
            "(END"+std::to_string(counts)+")"};
    }
    std::vector<std::string> writeAnd()
    {
        return {"@SP","AM=M-1","D=M","A=A-1","M=D&M"};
    }
    std::vector<std::string> writeOr()
    {
        return {"@SP","AM=M-1","D=M","A=A-1","M=D|M"};
    }
    std::vector<std::string> writeNot()
    {
        return {"@SP","A=M-1","M=!M"};
    }
    std::vector<std::string> writeNeg()
    {
        return {"@SP","A=M-1","M=-M"};
    }
};
