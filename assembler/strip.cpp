#include<iostream>
#include<fstream>
#include<string>

int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cout<<"読みたいファイルパスを入力して"<<std::endl;
    }
    //.asmファイルを開く
    std::ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        std::cerr<<"ファイルが開けませんでした"<<std::endl;
        return 1;
    }
    //開いたファイルを一行ずつ読む
    std::string line;
    std::string commentout("//");
    while(std::getline(ifs,line))
    {
        //コメントを取り除く
        std::string::size_type pos=line.find(commentout);
        if(pos!=std::string::npos)
            line.erase(pos);
        //空白を取り除く
        std::string result;
        for(char c:line)
        {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                // c はスペース・タブ・\n・\r などの空白
                result +=c;
            }
        }
        line=result;
        if(line.empty())
            continue;
        std::cout<<"["<<line<<"]"<<std::endl;
    }
    return 0;
}
