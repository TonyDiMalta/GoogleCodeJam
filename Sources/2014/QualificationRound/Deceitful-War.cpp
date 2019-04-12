#include <algorithm>
#include <iostream>

#include "Qualification-Round-2014.hpp"

constexpr unsigned int nb_max_blocks_per_player = 1000;
// The boolean is used to identify the 2 players, true for Naomi and false for Ken
std::pair<double, bool> woods_height[2 * nb_max_blocks_per_player];

std::pair<int, int> Play_Deceitful_War(const unsigned int& nb_total_blocks)
{
    unsigned int block_index = 0;
    int sum_war_points = 0;
    int sum_deceitful_war_points = 0;
    std::pair<int, int> optimal_scores = { 0, 0 };

    std::sort(woods_height, woods_height + nb_total_blocks, std::greater<std::pair<double, bool>>());

    for (block_index = 0; block_index < nb_total_blocks; ++block_index)
    {
        if (woods_height[block_index].second)
        {
            ++sum_war_points;
            ++sum_deceitful_war_points;

            optimal_scores.second = std::max(optimal_scores.second, sum_war_points);
        }
        else
        {
            --sum_war_points;

            if (sum_deceitful_war_points > 0)
            {
                --sum_deceitful_war_points;
                ++optimal_scores.first;
            }
        }
    }

    return optimal_scores;
}

void QR_2014::Solve_Deceitful_War(std::istream& input_stream, std::ostream& output_stream)
{
    unsigned int nb_cases = 0;
    unsigned int index = 0;
    unsigned int nb_blocks_per_player = 0;
    unsigned int nb_total_blocks = 0;
    unsigned int block_index = 0;
    std::pair<int, int> optimal_scores;

    input_stream >> nb_cases;
    for (index = 1; index <= nb_cases; ++index)
    {
        output_stream << "Case #" << index << ": ";

        input_stream >> nb_blocks_per_player;

        for (block_index = 0; block_index < nb_blocks_per_player; ++block_index)
        {
            input_stream >> woods_height[block_index].first;
            woods_height[block_index].second = true;
        }

        nb_total_blocks = 2 * nb_blocks_per_player;
        for (block_index = nb_blocks_per_player; block_index < nb_total_blocks; ++block_index)
        {
            input_stream >> woods_height[block_index].first;
            woods_height[block_index].second = false;
        }

        optimal_scores = Play_Deceitful_War(nb_total_blocks);

        output_stream << optimal_scores.first << ' ' << optimal_scores.second << '\n';
    }
}
