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
    }
    else{
        std::cout<<"不合格　「"<<input<<"」\n"
        <<"　正しい　；"<<expected<<"（"<<expected.size()<<"文字\n"
        <<"　出力　:"<<actual<<"（"<<actual.size()<<"文字\n";
        ++failed;
    }
}

void checkNotExist(std::string input)
{
    if(addressMap.contains(input))
    {
        std::cout<<"カッコ付きラベルが追加されています\n";
        ++failed;
    }else
    {
        std::cout<<"カッコ付きラベルは追加されていません\n";
    }
}

int main()
{
    MapLabel("(LOOP)",2);
    MapLabel("(LOOP)",5);
    MapLabel("(END)",18);
    for(const auto& [key,value]:addressMap)
    {
        std::cout<<key<<" ：　"<<value<<std::endl;
    }
    checkNotExist("(LOOP)");
    check("LOOP","2");
    check("END","18");
    if(failed==0)
    {
        std::cout<<"全部合格\n";
        return 0;
    }
    
    std::cout<<failed<<"件が不合格\n";
    return 1;
}
