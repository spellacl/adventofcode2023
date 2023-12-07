#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <map>

int main(int argc, char * argv[])
{
    assert(argc == 2);

    std::vector< std::pair<long long, long long> > races;
    if(strcmp(argv[1], "test") == 0)
    {
        races.push_back( std::make_pair(7,9));
        races.push_back( std::make_pair(15,40));
        races.push_back( std::make_pair(30, 200));
    }
    else if(strcmp(argv[1], "test1") == 0)
    {
        races.push_back( std::make_pair(42,284));
        races.push_back( std::make_pair(68,1005));
        races.push_back( std::make_pair(69, 1122));
        races.push_back( std::make_pair(85, 1341));
    }
    else
    {
        races.push_back(std::make_pair(42686985, 284100511221341));
    }

    long long score = 1;
    for(auto& race: races)
    {
        long long wins = 0;
        for(long long i = floor(race.first/2.0); i >= 0; i--)
        {
           // std::cout << i << " " << i * (race.first-i) << std::endl;
            bool win = i * (race.first-i) > race.second;
            wins += win;
            if(!win) break;
        }
        if(race.first % 2 == 0)
            wins = wins * 2 - 1;
        else
            wins *= 2;
        score *= wins;
        std::cout << wins << std::endl;
    }
    std::cout << score << std::endl;
    return 0;
}
