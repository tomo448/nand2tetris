#include"parts.h"
#include<iostream>
#include<string>
#include<vector>

int failed=0;

void check(std::ifstream& input,int expected)
{
    std::vector<std::string> con=PutInContainer(input);
    int actual =con.size();
    if(expected!=actual)
    {
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
    
    check(ifs,19);
    if(failed==0)
    {
        std::cout<<"合格"<<std::endl;
        return 0;
    }else
    {
        std::cout<<"不合格"<<std::endl;
        return 1;
    }
    return 0;
}
