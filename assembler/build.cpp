#include"parts.h"
#include<iostream>
#include<fstream>
#include<string>

int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cout<<"読みたいファイルパスを入力して"<<std::endl;
        return 1;
    }
    
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"ifsファイルが開けませんでした"<<std::endl;
        return 1;
    }
    
    std::ofstream ofs(argv[2]);
    if(!ofs.is_open())
    {
        std::cerr<<"ofsファイルが開けませんでした"<<std::endl;
        return 2;
    }
    std::string line;
    //１回目の走査
    std::vector<std::string> con=PutInContainer(ifs);
    FirstScan(con);
    
    //２回目の走査
    std::vector<std::string> text=SecondScan(con);
    for(auto& v:text)
    {
        ofs<<v<<std::endl;
    }
    ofs.close();
    return 0;
}
