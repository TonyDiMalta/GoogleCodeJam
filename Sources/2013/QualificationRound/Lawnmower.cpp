#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Qualification-Round-2013.hpp"

constexpr unsigned int MAX_SIZE = 100;
unsigned int lawn[MAX_SIZE][MAX_SIZE];
unsigned int nb_lines_used;
unsigned int nb_columns_used;

unsigned int Get_Max_Column_Height(unsigned int col_index) noexcept
{
    unsigned int max_height = lawn[0][col_index];

    for (unsigned int line_index = 1; line_index < nb_lines_used; ++line_index)
    {
        max_height = std::max(max_height, lawn[line_index][col_index]);
    }

    return max_height;
}

std::string Check_Lawn_Possible()
{
    unsigned int line_index = 0;
    unsigned int column_index = 0;
    unsigned int max_line_height = 0;
    std::vector<unsigned int> max_columns_height;

    for (column_index = 0; column_index < nb_columns_used; ++column_index)
    {
        max_columns_height.push_back(Get_Max_Column_Height(column_index));
    }

    for (line_index = 0; line_index < nb_lines_used; ++line_index)
    {
        max_line_height = *std::max_element(lawn[line_index], lawn[line_index] + nb_columns_used);

        for (column_index = 0; column_index < nb_columns_used; ++column_index)
        {
            if (lawn[line_index][column_index] != std::min(max_line_height, max_columns_height[column_index]))
            {
                return "NO";
            }
        }
    }

    return "YES";
}

void QR_2013::Solve_Lm(std::istream& file_input, std::ostream& file_output)
{
    unsigned int nb_lawns = 0;
    unsigned int lawn_index = 0;
    unsigned int line_index = 0;
    unsigned int column_index = 0;

    file_input >> nb_lawns;
    for (lawn_index = 1; lawn_index <= nb_lawns; ++lawn_index)
    {
        file_output << "Case #" << lawn_index << ": ";

        file_input >> nb_lines_used >> nb_columns_used;
        for (line_index = 0; line_index < nb_lines_used; ++line_index)
        {
            for (column_index = 0; column_index < nb_columns_used; ++column_index)
            {
                file_input >> lawn[line_index][column_index];
            }
        }

        file_output << Check_Lawn_Possible() << '\n';
    }
}
