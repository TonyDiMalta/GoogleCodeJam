#include <iostream>
#include <map>

#include "Round-1B-2019.hpp"

void Increment_Direction_Occurrences(std::map<unsigned int, int>& direction_occurrences, unsigned int position)
{
    if (direction_occurrences.find(position) != direction_occurrences.end())
    {
        ++direction_occurrences.at(position);
    }
    else
    {
        direction_occurrences.insert({ position, 1 });
    }
}

void Decrement_Direction_Occurrences(std::map<unsigned int, int>& direction_occurrences, unsigned int position)
{
    if (direction_occurrences.find(position) != direction_occurrences.end())
    {
        --direction_occurrences.at(position);
    }
    else
    {
        direction_occurrences.insert({ position, -1 });
    }
}

unsigned int Get_Maximum_Direction_Occurrences(std::map<unsigned int, int>& direction_occurrences)
{
    unsigned int best_position = 0;
    int best_position_occurrences = 0;
    int current_position_occurrences = 0;
    
    for (auto& direction_occurrence : direction_occurrences)
    {
        current_position_occurrences += direction_occurrence.second;

        if (current_position_occurrences > best_position_occurrences)
        {
            best_position = direction_occurrence.first;
            best_position_occurrences = current_position_occurrences;
        }
    }

    return best_position;
}

struct Position {
    unsigned int X;
    unsigned int Y;
};

void R1B_2019::Solve_Manhattan_Crepe_Cart(std::istream& input_stream, std::ostream& output_stream)
{
    unsigned int index_test_case = 0;
    unsigned int nb_test_cases = 0;
    unsigned int index_people = 0;
    unsigned int nb_people = 0;
    unsigned int position_limit = 0;
    char person_direction = 0;
    Position person_position = { 0, 0 };
    Position crepe_cart_position = { 0, 0 };
    std::map<unsigned int, int> directionX_occurrences;
    std::map<unsigned int, int> directionY_occurrences;

    input_stream >> nb_test_cases;
    for (index_test_case = 1; index_test_case <= nb_test_cases; ++index_test_case)
    {
        input_stream >> nb_people >> position_limit;

        for (index_people = 0; index_people < nb_people; ++index_people)
        {
            input_stream >> person_position.X >> person_position.Y >> person_direction;

            switch (person_direction)
            {
                case 'E':
                    Increment_Direction_Occurrences(directionX_occurrences, person_position.X + 1);
                    break;
                case 'W':
                    Decrement_Direction_Occurrences(directionX_occurrences, person_position.X);
                    break;

                case 'N':
                    Increment_Direction_Occurrences(directionY_occurrences, person_position.Y + 1);
                    break;
                case 'S':
                    Decrement_Direction_Occurrences(directionY_occurrences, person_position.Y);
                    break;

                default:
                    break;
            }
        }

        crepe_cart_position.X = Get_Maximum_Direction_Occurrences(directionX_occurrences);
        crepe_cart_position.Y = Get_Maximum_Direction_Occurrences(directionY_occurrences);

        output_stream << "Case #" << index_test_case << ": " <<
            crepe_cart_position.X << ' ' << crepe_cart_position.Y << '\n';

        directionX_occurrences.clear();
        directionY_occurrences.clear();
    }
}

/*int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    Solve_Manhattan_Crepe_Cart(std::cin, std::cout);
}*/
