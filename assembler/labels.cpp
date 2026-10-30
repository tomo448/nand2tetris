#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>

int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cout<<"読みたいファイルパスを入力して"<<std::endl;
        return 1;
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
    std::string parenthesis1("(");
    std::string parenthesis2(")");
    std::unordered_map<std::string,int> table;
    int i=0;
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
        //std::cout<<"["<<line<<"]"<<std::endl;
        std::string::size_type pos2=line.find(parenthesis1);
        std::string::size_type pos3=line.find(parenthesis2);
        if(pos2!=std::string::npos)
        {
            std::string result2=line.substr(pos2+1,pos3-pos2-1);
            table[result2]=i;
            continue;
        }
        i++;
    }
    for(const auto& p:table)
    {
        std::cout<<p.first<<" "<<p.second<<std::endl;
    }
    return 0;
}
