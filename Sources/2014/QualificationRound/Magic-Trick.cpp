#include <algorithm>
#include <fstream>
#include <string>

#include "Qualification-Round-2014.hpp"

void QR_2014::Solve_MT(std::ifstream& file_input, std::ofstream& file_output)
{
    constexpr unsigned int CARDS_PER_ROW = 4;
    unsigned int chosen_cards[CARDS_PER_ROW] = { 0 };

    unsigned int nb_tricks = 0;
    unsigned int volunteer_index = 0;
    unsigned int line_index = 0;
    unsigned int column_index = 0;
    unsigned int chosen_row = 0;
    unsigned int throw_value = 0;
    unsigned int nb_matching_cards = 0;
    std::string magician_reveal;

    file_input >> nb_tricks;
    for (volunteer_index = 1; volunteer_index <= nb_tricks; ++volunteer_index)
    {
        file_output << "Case #" << volunteer_index << ": ";

        file_input >> chosen_row;

        for (line_index = 0; line_index < CARDS_PER_ROW; ++line_index)
        {
            if (line_index + 1 == chosen_row)
            {
                for (column_index = 0; column_index < CARDS_PER_ROW; ++column_index)
                {
                    file_input >> chosen_cards[column_index];
                }
            }
            else
            {
                for (column_index = 0; column_index < CARDS_PER_ROW; ++column_index)
                {
                    file_input >> throw_value;
                }
            }
        }

        file_input >> chosen_row;

        for (line_index = 0, nb_matching_cards = 0; line_index < CARDS_PER_ROW; ++line_index)
        {
            if (line_index + 1 == chosen_row)
            {
                for (column_index = 0; column_index < CARDS_PER_ROW; ++column_index)
                {
                    file_input >> throw_value;

                    nb_matching_cards += static_cast<unsigned int>(std::count(chosen_cards, chosen_cards + CARDS_PER_ROW, throw_value));

                    if (nb_matching_cards == 1 &&
                        magician_reveal.empty())
                    {
                        magician_reveal = std::to_string(throw_value);
                    }
                }
            }
            else
            {
                for (column_index = 0; column_index < CARDS_PER_ROW; ++column_index)
                {
                    file_input >> throw_value;
                }
            }
        }

        if (nb_matching_cards == 0)
        {
            magician_reveal = "Volunteer cheated!";
        }
        else if (nb_matching_cards > 1)
        {
            magician_reveal = "Bad magician!";
        }

        file_output << magician_reveal << '\n';

        magician_reveal.clear();
    }
}
