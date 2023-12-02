#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

int main(int argc, char * argv[])
{
    assert(argc == 2);
    std::ifstream ifs; // input file stream
    std::string str;
    ifs.open(argv[1], std::ios::in );

    std::vector<std::pair<std::string, int>> num = {{std::string("one"),  1},
                                                    {std::string("two"),  2},
                                                    {std::string("three"),3},
                                                    {std::string("four"), 4},
                                                    {std::string("five"), 5},
                                                    {std::string("six"),  6},
                                                    {std::string("seven"),7},
                                                    {std::string("eight"),8},
                                                    {std::string("nine"), 9}
                                                    };

    if(ifs)
    {
        int count = 0;
        while ( !ifs.eof() )
        {
            std::getline ( ifs, str);
            std::cout << str << std::endl;

            int first = 0, last = 0;
            size_t len = str.length() + 1;
            size_t first_digit_loc = len;
            size_t last_digit_loc = 0;

            if(size_t loc = str.find_first_of("0123456789");
                loc != std::string::npos)
            {
                first_digit_loc = loc;
                first = str[loc] - '0';
            }
            if(size_t loc = str.find_last_of("0123456789");
                loc != std::string::npos)
            {
                last_digit_loc = loc;
                last = str[loc] - '0';;
            }

            for(auto& pair: num)
            {
                size_t first_pos = str.find(pair.first);
                size_t last_pos =  str.rfind(pair.first);

                if(first_pos != std::string::npos && first_pos < first_digit_loc)
                {
                    first_digit_loc = first_pos;
                    first = pair.second;
                }
                if(last_pos != std::string::npos && last_pos > last_digit_loc)
                {
                    last_digit_loc = last_pos;
                    last = pair.second;
                }
            }

            count += 10* first + last;
            std::cout << first << " " << last << " " << count << std::endl;
        }
        ifs.close();
    }

    return 0;
}
