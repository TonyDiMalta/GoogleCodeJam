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

void QR_2019::Solve_You_Can_Go_Your_Own_Way(std::istream& input_stream, std::ostream& output_stream)
{
    std::string forbidden_path;
    std::string valid_path;
    unsigned int maze_dimensions = 0;
    unsigned int index_test_case = 0;
    unsigned int nb_test_cases = 0;

    input_stream >> nb_test_cases;
    for (index_test_case = 1; index_test_case <= nb_test_cases; ++index_test_case)
    {
        output_stream << "Case #" << index_test_case << ": ";

        input_stream >> maze_dimensions;

        input_stream.ignore();
        input_stream.sync();
        std::getline(input_stream, forbidden_path);

        valid_path = Solve_Maze(forbidden_path);

        output_stream << valid_path << '\n';
    }
}
