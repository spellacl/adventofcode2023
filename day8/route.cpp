#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>

int main(int argc, char *argv[])
{
    assert(argc == 2);

    std::ifstream myfile;
    myfile.open(argv[1]);

    std::string str;

    std::string rules;
    std::getline(myfile, rules);
    std::getline(myfile, str);

    std::map<std::string, std::pair<std::string, std::string>> map;

    while(std::getline(myfile, str))
    {
        std::cout << str << std::endl;

        size_t pos = str.find('=');
        size_t pos2 = str.find(',');

        map[str.substr(0, 3)] = std::make_pair(str.substr(pos2-3,3), str.substr(pos2+2,3));
    }
    for(auto &m : map)
    {
        std::cout << m.first << "(" << m.second.first << "," << m.second.second << ")" << std::endl;
    }

    int iter = 0;
    int len = rules.size();
    std::string curr("AAA"), next;
    std::string finish = std::string("ZZZ");
    while(curr != finish)
    {
        if(rules.at(iter%len) == 'L')
        {
            next = map.at(curr).first;
        }
        else
        {
            next = map.at(curr).second;
        }
        iter += 1;
        std::cout << curr << " "  << next << " " << iter << std::endl;
        curr = next;
    }

    myfile.close();
    return 0;
}
