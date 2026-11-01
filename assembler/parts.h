#include<string>
#include<format>

std::string ParserA(std::string a_command)
{
    //@を飛ばす．命令の判定は他の関数．ここにくるのはA命令でエラー判定しない
    std::string value =a_command.substr(1);
    int num=std::stoi(value);
    std::string binstr=std::format("{:016b}",num);
    return binstr;
}
