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
        int score = 0;
        while (std::getline(ifs, str) && !ifs.eof() )
        {
            std::cout << str << std::endl;

            size_t pos_colon = str.find(":");
            std::string game = str.substr(5, pos_colon - 5);

            bool game_possible = true;

            size_t pos_old = pos_colon, pos;

            std::map<std::string, int> num = {
                            {std::string("blue"),  0},
                            {std::string("red"),   0},
                            {std::string("green"), 0}
                        };

//            auto check_game = [&num](const std::string tmp, bool &game_possible)
            auto check_game = [&num](const std::string tmp)
            {
                //for(auto iter = num.cbegin(); iter != num.cend(); ++iter)
                for(auto iter = num.begin(); iter != num.end(); ++iter)
                {
                    if(size_t p = tmp.find(iter->first); p!=std::string::npos)
                    {
                        std::string val;
                        p = p - 2;
                        while(std::isdigit(tmp[p]))
                        {
                            val.insert(0, tmp.substr(p,1));
                            p--;
                        }

                        if(int val_int = std::stoi(val); val_int > iter->second)
                        {
                            //game_possible = false;
                            //break;
                            iter->second = val_int;
                        }
                    }
                }
            };

            while(game_possible && (pos = str.find(";", pos_old)) && pos != std::string::npos)
            {
                std::string tmp = str.substr(pos_old+1, pos-pos_old);
                //check_game(tmp, game_possible);
                check_game(tmp);

                pos_old = pos + 1;
            }
            //if(game_possible) check_game(str.substr(pos_old), game_possible);
            //std::cout << "Game " << game << ": " << game_possible << std::endl;
            //if(game_possible) score += std::stoi(game);

            check_game(str.substr(pos_old));
            int power = 1;
            for(auto it = num.cbegin(); it != num.cend(); it++)
            {
                power *= it->second;
            }
               
            std::cout << "Game " << game << " :" << power << std::endl;
            score += power;
        }
        std::cout << "Total: " << score << std::endl;
        ifs.close();
    }

    return 0;
}
