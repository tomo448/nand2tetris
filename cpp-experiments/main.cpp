#include"parts.h"

int main()
{
    std::cout<<"実験１"<<std::endl;
    Tracker t;
    Parser p(t);
    std::cout<<"実験２"<<std::endl;
    Parser pp{Tracker()};
    std::cout<<"実験３"<<std::endl;
    const Tracker ct;
    Parser p3{std::move(ct)};
    return 0;
}
