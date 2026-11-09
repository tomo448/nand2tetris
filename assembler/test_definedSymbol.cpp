#include<iostream>
#include<string>
#include"parts.h"

int failed=0;

void check(const std::string& input,const std::string& expected)
{
    std::string actual=std::to_string(addressMap.at(input));
    if(actual==expected)
    {
        std::cout<<"合格　「"<<input<<"」\n";
    }else
    {
        std::cout<<"不合格　「"<<input<<"」\n"
        <<"　正しい；　"<<expected<<" ("<<expected.size()<<"文字)\n"
        <<"　　出力；　"<<actual<<"("<<actual.size()<<"文字)\n";
        ++failed;
    }
}

int main()
{
    check("SCREEN","16384");
    check("KBD","24576");
    check("R15","15");
    check("SP","0");
    check("LCL","1");
    check("THIS","3");
    if(failed==0)
    {
        std::cout<<"全部合格\n";
        return 0;
    }
    
    std::cout<<failed<<"件が不合格\n";
    return 1;
}
