#include <iostream>
#include <string>

#include "Qualification-Round-2015.hpp"

unsigned int Minimum_Number_Of_Friends(const unsigned int& max_shyness_level, const std::string& audience_shyness_level)
{
    unsigned int min_nb_friends = 0;
    unsigned int nb_people_standing = 0;
    unsigned int shyness_level = 0;

    for (shyness_level = 0; shyness_level <= max_shyness_level; ++shyness_level)
    {
        if (nb_people_standing < shyness_level)
        {
            min_nb_friends += shyness_level - nb_people_standing;
            nb_people_standing = shyness_level;
        }

        nb_people_standing += audience_shyness_level[shyness_level] - '0';
    }

    return min_nb_friends;
}

void QR_2015::Solve_Standing_Ovation(std::istream& file_input, std::ostream& file_output)
{
    unsigned int nb_audiences = 0;
    unsigned int audience_index = 0;
    unsigned int max_shyness_level = 0;
    unsigned int min_nb_friends = 0;
    std::string audience_shyness_level;

    file_input >> nb_audiences;
    for (audience_index = 1; audience_index <= nb_audiences; ++audience_index)
    {
        file_output << "Case #" << audience_index << ": ";

        file_input >> max_shyness_level >> audience_shyness_level;

        min_nb_friends = Minimum_Number_Of_Friends(max_shyness_level, audience_shyness_level);

        file_output << min_nb_friends << '\n';
    }
}
