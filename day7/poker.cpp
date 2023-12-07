#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <map>
#include <algorithm>

int main(int argc, char * argv[])
{
    assert(argc == 2);
    std::ifstream ifs; // input file stream
    std::string str;
    ifs.open(argv[1], std::ios::in );

    if(ifs)
    {
        std::map<int, std::vector<std::pair<std::string, int>>>
            ranks;
        long long score = 0;
        while (std::getline(ifs, str) && !ifs.eof() )
        {
            std::map<char, int> count;
            size_t pos = str.find(' ');
            std::string cards = str.substr(0, 5);
            int bid = std::stoi(str.substr(pos+1));
            std::cout << cards << " " << bid << std::endl;
            for(auto& c : cards)
            {
                count[c] += 1;
            }

            int size = count.size();
            if(size == 1)
            {
                ranks[6].push_back(std::make_pair(cards, bid));
            }
            else if(size == 2)
            {
                if(std::any_of(count.cbegin(), count.cend(), 
                             [](const auto& p) { return p.second  == 4; })) 
                    ranks[5].push_back(std::make_pair(cards, bid));
                else
                    ranks[4].push_back(std::make_pair(cards, bid));
            }
            else if(size == 3)
            {
                if(std::any_of(count.cbegin(), count.cend(), 
                                     [](const auto& p) { return p.second  == 3; })) 
                    ranks[3].push_back(std::make_pair(cards, bid));
                else
                    ranks[2].push_back(std::make_pair(cards, bid));
            }
            else if(size == 4)
            {
                ranks[1].push_back(std::make_pair(cards, bid));
            }
            else if(size == 5)
            {
                ranks[0].push_back(std::make_pair(cards, bid));
            }
        }

        for(auto& rank : ranks)
        {
            std::sort(rank.second.begin(), rank.second.end(),
                [](auto p, auto q)
                {
                    std::map<char, int> card_score ={ { 'A', 14 },
                                                      { 'K', 13 },
                                                      { 'Q', 12 },
                                                      { 'J', 11 },
                                                      { 'T', 10 },
                                                      { '9',  9 },
                                                      { '8',  8 },
                                                      { '7',  7 },
                                                      { '6',  6 },
                                                      { '5',  5 },
                                                      { '4',  4 },
                                                      { '3',  3 },
                                                      { '2',  2 } };
                    for(int i = 0; i < 5; i++)
                    {
                        if(p.first.at(i) == q.first.at(i))
                            continue;
                        else if(card_score[p.first.at(i)] < card_score[q.first.at(i)])
                            return true;
                        else
                            return false;  
                    }
                    return false;
                });
        }

        int position = 1;
        for(auto &rank : ranks)
        {
            //std::cout << "================================================" <<  rank.first << std::endl;
            for(auto &str : rank.second)
            {
            //    std::cout << str.first << " " << position << " " << str.second << std::endl;
                score += position * str.second;
                position += 1;
            }
        }

        std::cout << "Total score: " << score << std::endl;
        ifs.close();
    }

    return 0;
}
