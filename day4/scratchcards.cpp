#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <map>

int main(int argc, char * argv[])
{
    assert(argc == 2);
    std::ifstream ifs; // input file stream
    std::string str;
    ifs.open(argv[1], std::ios::in );

    if(ifs)
    {
        long long score = 0;
        long long total_cards = 0;
        std::map<int, std::pair<int, int>> games;
        while (std::getline(ifs, str) && !ifs.eof() )
        {
            std::cout << str << std::endl;

            size_t pos_colon = str.find(":");
            std::string game = str.substr(4, pos_colon - 4);

            size_t pos_line = str.find("|");
            std::string tmp_value;
            std::vector<int> winners;
            for(int it = pos_colon + 2; it < pos_line; it++)
            {
                if(std::isdigit(str.at(it)))
                    tmp_value.push_back(str.at(it));
                else if(!tmp_value.empty())
                {
                    winners.push_back(std::stoi(tmp_value));
                    tmp_value.clear();
                }
            }
            for(auto & win : winners)
                std::cout << win << std::endl;

            int points = 0;
            tmp_value.clear();

            games[std::stoi(game)] = std::make_pair(0,1);
            for(int it = pos_line + 1; it < str.length(); it++)
            {
                if(std::isdigit(str.at(it)))
                    tmp_value.push_back(str.at(it));

                if((std::isspace(str.at(it)) && !tmp_value.empty())
                    || it == str.length() -1)
                {
                    if(auto found = find(winners.cbegin(), winners.cend(), std::stoi(tmp_value)); 
                        found != std::end(winners))
                    {
                        points = (points == 0) ? 1 : points * 2;
                        games.at(std::stoi(game)).first +=1;
                    }
                    tmp_value.clear();
                }
            }
            score += points;
        }

        for(auto it = games.begin(); it != games.end(); it++)
        {
            // iterate over number of cards you've got
            for(int i = 0; i < (it->second).second; i++)
            {
                // iterate over number of wins for that card.
                for(int j = 1; j <= (it->second).first; j++)
                {
                    games.at(it->first + j).second += 1;
                }
            }
        }


        for(auto it = games.begin(); it != games.end(); it++)
        {
            total_cards += (it->second).second;
        }
        std::cout << "Total score: " << score << std::endl;
        std::cout << "Total cards: " << total_cards << std::endl;

        ifs.close();
    }

    return 0;
}
