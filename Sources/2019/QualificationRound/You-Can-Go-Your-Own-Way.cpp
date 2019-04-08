#include <iostream>
#include <string>

#include "Qualification-Round-2019.hpp"

std::string Solve_Maze(std::string& forbidden_path)
{
    std::string valid_path;

    for (const auto& forbidden_direction : forbidden_path)
    {
        if (forbidden_direction == 'S')
        {
            valid_path.push_back('E');
        }
        else
        {
            valid_path.push_back('S');
        }
    }

    return valid_path;
}

void QR_2019::Solve_OW(std::istream& input, std::ostream& output)
{
    std::string forbidden_path;
    std::string valid_path;
    unsigned int maze_dimensions = 0;
    unsigned int index_test_case = 0;
    unsigned int nb_test_cases = 0;

    input >> nb_test_cases;
    for (index_test_case = 1; index_test_case <= nb_test_cases; ++index_test_case)
    {
        output << "Case #" << index_test_case << ": ";

        input >> maze_dimensions;

        input.ignore();
        input.sync();
        std::getline(input, forbidden_path);

        valid_path = Solve_Maze(forbidden_path);

        output << valid_path << '\n';
    }
}
