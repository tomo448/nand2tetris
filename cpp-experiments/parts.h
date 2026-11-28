#include<iostream>

class Tracker
{
public:
    Tracker()
    {
        std::cout<<"コンストラクタが呼ばれた"<<std::endl;
    }
    Tracker(const Tracker& rhs)
    {
        std::cout<<"コピーコンストラクタが呼ばれた"<<std::endl;
    }
    Tracker& operator=(const Tracker& rhs)
    {
        std::cout<<"コピー代入演算子が呼ばれた"<<std::endl;
        return *this;
    }
    Tracker(Tracker&& rhs)noexcept
    {
        std::cout<<"ムーブコンストラクタが呼ばれた"<<std::endl;
    }
    Tracker& operator=(Tracker&& rhs)
    {
        std::cout<<"ムーブ代入演算子が呼ばれた"<<std::endl;
        return *this;
    }
};

class Parser
{
    Tracker _tracker;
public:
    Parser(Tracker t):_tracker(std::move(t)){}
};
