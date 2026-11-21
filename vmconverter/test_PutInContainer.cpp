#include"parts.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

int failed=0;

void check(std::ifstream& ifs,const std::vector<std::string>& expected1,size_t expected2)
{
    std::vector<std::string> actual=PutInContainer(ifs);
    for(auto c:actual)
    {
        std::cout<<"出力"<<std::endl;
        std::cout<<c<<std::endl;
        std::cout<<"文字の長さ:"<<c.length()<<std::endl;
    }
    for(auto c:expected1)
    {
        std::cout<<"正解"<<std::endl;
        std::cout<<c<<std::endl;
        std::cout<<"文字の長さ:"<<c.length()<<std::endl;
    }
    if(actual!=expected1)
    {
        failed++;
        std::cout<<"命令が一致しません"<<std::endl;
        return;
    }
    if(actual.size()!=expected2)
    {
        failed++;
        std::cout<<"行数が一致しません"<<std::endl;
        return;
    }
}
int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cerr<<"ファイルパスを入力してください"<<std::endl;
        return 1;
    }
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"ファイルが開けません"<<std::endl;
        return 2;
    }
    check(ifs,{"push constant 7","add"},2);
    if(failed==0)
    {
        std::cout<<"合格"<<std::endl;
    }
    else
    {
        std::cout<<"不合格"<<std::endl;
        return 99;
    }
    return 0;
}
