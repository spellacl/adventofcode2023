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

    long long score = 0;
    if(ifs)
    {
        while(std::getline(ifs, str) && !str.empty())
        {
            std::cout << str << std::endl;
            size_t old_pos = 0, pos;

            std::vector<long> vec;
            while((pos = str.find(' ', old_pos)) != std::string::npos )
            {
                vec.push_back(std::stol(str.substr(old_pos, pos-old_pos)));
                old_pos = pos+1;
            }
            vec.push_back(std::stol(str.substr(old_pos)));


            long long last_val = *(vec.end() - 1);

            std::vector<long> curr = vec, next;
            while(! std::all_of(curr.cbegin(), curr.cend(), [](auto i){ return i == 0; }))
            {
                for(auto it = curr.cbegin(); it != curr.cend()-1; it++)
                    next.push_back(*(it+1) - *(it));
                curr = next;
                last_val += *(next.end()-1);
                next.clear();
            }

            score += last_val;
            std::cout << last_val << std::endl;
        }

        std::cout << "Total score: " << score << std::endl;
        ifs.close();
    }

    return 0;
}
