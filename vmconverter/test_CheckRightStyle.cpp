#include"parts.h"
#include<string>
#include<iostream>
#include<vector>
#include<stdexcept>
int failed=0;

void check(const std::vector<std::string>& input)
{
    std::cout<<"入力:";
    for(auto c:input)
        std::cout<<c<<" ";
    try {
        CheckRightStyle(input);
    } catch (std::exception& e) {
        std::cout<<"合格" <<std::endl;
        std::cerr<<e.what()<<std::endl;
        return ;
    }
    failed++;
    std::cout<<"不合格"<<std::endl;
}

void checkRight(const std::vector<std::string>& input)
{
    std::cout<<"入力:";
    for(auto c:input)
        std::cout<<c<<" ";
    try {
        CheckRightStyle(input);
    } catch (std::exception& e) {
        std::cout<<"不合格"<<std::endl;
        std::cerr<<e.what()<<std::endl;
        failed++;
        return;
    }
    std::cout<<"合格"<<std::endl;
}

int main()
{
    check({"push","constant"});
    check({"add","3"});
    check({"push","constant","x"});
    checkRight({"push","constant","7"});
    check({});
    check({"push","loacl","3"});
    check({"pop","constant","5"});
    if(failed==0)
    {
        std::cout<<"全部合格"<<std::endl;
    }else{
        std::cout<<failed<<"件不合格"<<std::endl;
    }
}
