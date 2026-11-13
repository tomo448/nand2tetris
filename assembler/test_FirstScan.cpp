#include"parts.h"
#include<iostream>
#include<string>
#include<vector>

int failed=0;

void check(const std::string& input,int expected)
{
    int actual =addressMap.at(input);
    if(expected==actual)
    {
        std::cout<<"　合格 「"<<input<<"」"<<std::endl;
    }else
    {
        std::cout<<"　不合格 「"<<input<<"」"<<std::endl;
        std::cout<<"正しい　："<<expected<<std::endl;
        std::cout<<"出力　："<<actual<<std::endl;
        failed++;
    }
}
int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cout<<"読みたいファイルを指定してください"<<std::endl;
        return  1;
    }
    
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"ファイルが開けません"<<std::endl;
        return 2;
    }
    std::vector<std::string> con=PutInContainer(ifs);
    FirstScan(con);
    check("ITSR0",10);
    check("OUTPUT_D",12);
    check("END",14);
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
        return 0;
    }else
    {
        std::cout<<failed<<"件不合格"<<std::endl;
        return 1;
    }
    return 0;
}
