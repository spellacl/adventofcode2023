#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <cassert>

void north(std::vector<std::string>& dish_in, std::vector<std::string> dish_out, const size_t& row, const size_t& width)
{
    dish_out.at(0) = dish_in.at(0);

    for(int i = 1; i < row; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //std::cout << (dish.at(i)).at(j) << " (" << i << "," << j << ") -> (";
            if((dish_in.at(i)).at(j) == 'O')
            {
                int k = i;
                while(k != 0 && (dish_out.at(k-1)).at(j) != 'O' && (dish_out.at(k-1)).at(j) != '#')
                {
                    k -= 1;
                }
                //std::cout << k << "," << j << ")";
                (dish_out.at(k)).at(j) = 'O';
            }
            //std::cout << std::endl;
        }
    }
    dish_in = dish_out;
}

void south(std::vector<std::string>& dish_in, std::vector<std::string> dish_out, const size_t& row, const size_t& width)
{
    *(dish_out.end()-1) = *(dish_in.end()-1);

    for(int i = row-2; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            //std::cout << (dish.at(i)).at(j) << " (" << i << "," << j << ") -> (";
            if((dish_in.at(i)).at(j) == 'O')
            {
                int k = i;
                while(k != row-1 && (dish_out.at(k+1)).at(j) != 'O' && (dish_out.at(k+1)).at(j) != '#')
                {
                    k += 1;
                }
                //std::cout << k << "," << j << ")";
                (dish_out.at(k)).at(j) = 'O';
            }
            //std::cout << std::endl;
        }
    }
    dish_in = dish_out;
}

void west(std::vector<std::string>& dish_in, std::vector<std::string> dish_out, const size_t& row, const size_t& width)
{
    for(int i = 0; i < row; i++)
        (dish_out.at(i)).at(0) = (dish_in.at(i)).at(0);

    for(int j = 1; j < width; j++)
    {
        for(int i = 0; i < row; i++)
        {
            //std::cout << (dish.at(i)).at(j) << " (" << i << "," << j << ") -> (";
            if((dish_in.at(i)).at(j) == 'O')
            {
                int k = j;
                while(k != 0 && (dish_out.at(i)).at(k-1) != 'O' && (dish_out.at(i)).at(k-1) != '#')
                {
                    k -= 1;
                }
                //std::cout << k << "," << j << ")";
                (dish_out.at(i)).at(k) = 'O';
            }
            //std::cout << std::endl;
        }
    }
    dish_in = dish_out;
}

void east(std::vector<std::string>& dish_in, std::vector<std::string> dish_out, const size_t& row, const size_t& width)
{
    for(int i = 0; i < row; i++)
        *((dish_out.at(i)).end()-1) = *((dish_in.at(i)).end()-1);

    for(int j = width-2; j >= 0; j--)
    {
        for(int i = 0; i < row; i++)
        {
            //std::cout << (dish.at(i)).at(j) << " (" << i << "," << j << ") -> (";
            if((dish_in.at(i)).at(j) == 'O')
            {
                int k = j;
                while(k != width-1 && (dish_out.at(i)).at(k+1) != 'O' && (dish_out.at(i)).at(k+1) != '#')
                {
                    k += 1;
                }
                //std::cout << k << "," << j << ")";
                (dish_out.at(i)).at(k) = 'O';
            }
            //std::cout << std::endl;
        }
    }
    dish_in = dish_out;
}

int main(int argc, char * argv[])
{
    assert(argc == 2);
    std::ifstream ifs; // input file stream
    std::string str;
    ifs.open(argv[1], std::ios::in );

    if(ifs)
    {
        long long score = 0;
        std::vector<std::string> dish, dish2;

        while (std::getline(ifs, str) && !ifs.eof() )
        {
            dish.push_back(str);
            std::replace(str.begin(), str.end(), 'O', '.');
            dish2.push_back(str);
        }

        size_t width = dish.at(0).size();
        size_t row   = dish.size();

        for(auto & s : dish2)
        {
            std::cout << s << std::endl;
        }

        std::cout << std::endl;
        long long last_score = 0;

        std::vector<std::pair<long long, size_t>> double_iter;
        for(size_t iter = 1 ; iter <= 1000000000; iter++)
        //for(size_t iter = 0 ; iter < 50; iter++)
        {
            north(dish, dish2, row, width);
            west (dish, dish2, row, width);
            south(dish, dish2, row, width);
            east (dish, dish2, row, width);

            score = 0;

            int k = row;
            for(auto & s : dish)
            {
                score += std::count_if(s.begin(), s.end(), [](auto i){ return i == 'O';}) * k;
                //std::cout << s << std::endl;
                k -= 1;
            }
            //std::cout << std::endl;
            std::cout << "Score [" << iter << "]: " << score << std::endl;

            if(last_score == score)
            {
                double_iter.push_back(std::make_pair(iter, score));
                std::cout << "------------------------------------------------------------" << std::endl;
                if(double_iter.size() > 4)
                    break;
            }
            last_score = score;
        }

        // Figured this one out manually because the second input had two repeaters
        // Find the last point before it starts repeating.
        // value = last_point + (1000000000 - last_point) % (length of repeater)
        for(auto & p : double_iter)
        {
            std::cout << p.first << " " << p.second << std::endl;
        }

        ifs.close();
    }

    return 0;
}
