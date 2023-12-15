#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <cassert>

int main(int argc, char * argv[])
{
    assert(argc == 2);
    std::ifstream ifs; // input file stream
    std::string str;
    ifs.open(argv[1], std::ios::in );

    auto hash = [](const std::string& str) -> long
    {
        long hash = 0;
        for(auto &c : str)
        {
            hash += int(c);
            hash *= 17;
            hash %= 256;
        }
        return hash;
    };

    std::string HASH = std::string("HASH");
    std::cout << hash(HASH) << std::endl;

    if(ifs)
    {
        long long score = 0;

        while (std::getline(ifs, str,',') && !ifs.eof())
        {
            std::cout << str << " "  << hash(str) << std::endl;
            score += hash(str);
        }
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
        std::cout << str << " "  << hash(str) << std::endl;
        score += hash(str);

        std::cout << "Score : " << score << std::endl;

        ifs.close();
    }

    return 0;
}
