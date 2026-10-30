#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> table;
    std::cout << table.size() << '\n';      // 予想:0
    std::cout << table["LOOP"] << '\n';     // 予想:null
    std::cout << table.size() << '\n';      // 予想:1
    std::cout << table["LOOP"] << '\n';　　　//予想:0
}

