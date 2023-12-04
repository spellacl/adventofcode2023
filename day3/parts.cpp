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
        std::map<std::pair<int, int>, char> grid;

        int Nrow = 0, Ncol=0;
        while (std::getline(ifs, str) && !ifs.eof() )
        {
            Ncol = 0;
            
            for(auto& c : str)
            {
                grid[std::make_pair(Nrow,Ncol)] = c;
                Ncol++;
            }
            Nrow ++;
        }

        auto is_symbol = [](char c) -> bool
        {
            return c != '.';
        };

        auto check_number = [&is_symbol, &grid, &Nrow, &Ncol]
                (int start, int end, int i) -> bool
        {
            bool is_part = false;
            if(i != 0)
            {
                for(int j = start; j <= end; j++)
                {
                    is_part |= is_symbol(grid[std::make_pair(i-1, j)]); 
                }
            }

            if(i != Nrow-1)
            {
                for(int j = start; j <= end; j++)
                {
                    is_part |= is_symbol(grid[std::make_pair(i+1, j)]); 
                }
            }

            if(start!=0)
            {
                is_part |= is_symbol(grid[std::make_pair(i, start-1)]);

                if(i != 0)
                    is_part |= is_symbol(grid[std::make_pair(i-1, start-1)]);
                if(i != Nrow-1)
                    is_part |= is_symbol(grid[std::make_pair(i+1, start-1)]);
            }
            if(end != Ncol-1)
            {
                is_part |= is_symbol(grid[std::make_pair(i, end + 1)]);

                if(i != 0)
                    is_part |= is_symbol(grid[std::make_pair(i-1, end+1)]);
                if(i != Nrow-1)
                    is_part |= is_symbol(grid[std::make_pair(i+1, end+1)]);
            }


            return is_part;
        };


        for(int i = 0; i < Nrow; i++)
        {
            for(int j = 0; j < Ncol; j++)
            {
                std::cout << grid.at(std::make_pair(i,j));
            }
            std::cout << std::endl;
        }

        int start_ind = -1;
        int end_ind = -1;

        for(int i = 0; i < Nrow; i++)
        {
            start_ind = -1;
            end_ind = -1;
            for(int j = 0; j < Ncol; j++)
            {
                if(std::isdigit( grid[std::make_pair(i,j)] ))
                {
                    if(start_ind == -1)
                        start_ind = j;
                    if(start_ind != -1 && j == Ncol -1)
                        end_ind = j;
                }
                else
                {
                    if(start_ind != -1)
                    {
                        end_ind = j-1;
                    }
                }

                if(end_ind != -1)
                {
                    std::string val;
                    if(check_number(start_ind, end_ind, i))
                    {
                        for(int k = start_ind; k <= end_ind; k++)
                        {
                                val.push_back(grid[std::make_pair(i,k)]);
                        }
                        score += std::stoi(val);    
                    }
                    start_ind = -1;
                    end_ind = -1;
                }
            }
        }

        std::cout << "Total: [" << Nrow << "," << Ncol << "]"  << score << std::endl;
        ifs.close();
    }

    return 0;
}
