#include <iostream>
#include <string>

#include "Qualification-Round-2019.hpp"

std::pair<std::string, std::string> Split_Integer(std::string integer_to_split)
{
    std::string first_integer;
    std::string second_integer;

    for (const auto& digit : integer_to_split)
    {
        if (digit == '4')
        {
            first_integer.push_back('2');
            second_integer.push_back('2');
        }
        else
        {
            first_integer.push_back(digit);
            second_integer.push_back('0');
        }
    }

    return { first_integer, second_integer };
}

void QR_2019::Solve_Foregone_Solution(std::istream& input_stream, std::ostream& output_stream)
{
    std::pair<std::string, std::string> pair_solution;
    std::string integer_to_split;
    unsigned int index_test_case = 0;
    unsigned int nb_test_cases = 0;

    input_stream >> nb_test_cases;
    for (index_test_case = 1; index_test_case <= nb_test_cases; ++index_test_case)
    {
        output_stream << "Case #" << index_test_case << ": ";

        input_stream >> integer_to_split;

        pair_solution = Split_Integer(integer_to_split);

        output_stream << pair_solution.first << ' ' << pair_solution.second << '\n';
    }
}
