#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Qualification-Round-2013.hpp"

// We want all fair and square numbers with digits <= 101, so we get the square
// roots bounded by length <= 2 * 25 + 1 = 51
constexpr unsigned int MAX_ROOT = 25;

std::vector<std::string> fair_and_square_numbers;

bool Compare_Numbers(const std::string& number1, const std::string& number2) noexcept
{
    const auto number1_size = number1.size();
    const auto number2_size = number2.size();

    if (number1_size < number2_size)
    {
        return true;
    }

    if (number1_size > number2_size)
    {
        return false;
    }

    return number1 < number2;
}

unsigned int Count_Numbers_In_Range(const std::string& range_min, const std::string& range_max)
{
    const auto min_iterator = std::lower_bound(fair_and_square_numbers.begin(), fair_and_square_numbers.end(), range_min, Compare_Numbers);
    if (min_iterator == fair_and_square_numbers.end())
    {
        return 0;
    }

    const auto max_iterator = std::upper_bound(min_iterator, fair_and_square_numbers.end(), range_max, Compare_Numbers);

    return static_cast<unsigned int>(std::distance(min_iterator, max_iterator));
}

std::string Square_Number(const std::string& number)
{
    const std::size_t number_size = number.size();
    std::string square(number_size * 2 - 1, '0');
    std::size_t i = 0;
    std::size_t j = 0;
    char val1 = 0;
    char val2 = 0;

    for (i = 0; i < number_size; ++i)
    {
        val1 = number[i] - '0';
        for (j = 0; j < number_size; ++j)
        {
            val2 = number[j] - '0';
            square[i + j] += val1 * val2;
        }
    }

    return square;
}

void Generate_Fair_and_Square_Numbers()
{
    std::cout << "Generating fair and square numbers...";

    // Manually adds the 1-digit values
    fair_and_square_numbers.push_back("1");
    fair_and_square_numbers.push_back("4");
    fair_and_square_numbers.push_back("9");

    unsigned int root_number = 0;
    unsigned int number_of_ones = 0;
    std::string half_palindrome;
    half_palindrome.reserve(MAX_ROOT);
    std::string reverse_half_palindrome;
    reverse_half_palindrome.reserve(MAX_ROOT);

    // Generates all candidate square roots of length <= 2 * MAX_ROOT + 1
    for (root_number = 1; root_number <= MAX_ROOT; ++root_number)
    {
        // There are between one and five 1s on the left half of the palindrome
        for (number_of_ones = 1; number_of_ones < 5 && number_of_ones <= root_number; ++number_of_ones)
        {
            half_palindrome.replace(half_palindrome.begin(), half_palindrome.end(), root_number, '0');
            half_palindrome[0] = '1';
            if (number_of_ones != 1)
            {
                half_palindrome.replace(half_palindrome.end() - number_of_ones + 1, half_palindrome.end(), number_of_ones - 1, '1');
            }

            // Get all possible locations for the 1s
            do
            {
                reverse_half_palindrome.resize(root_number);
                std::reverse_copy(half_palindrome.begin(), half_palindrome.end(), reverse_half_palindrome.begin());

                // Generate some candidates
                fair_and_square_numbers.push_back(Square_Number(half_palindrome + reverse_half_palindrome));
                fair_and_square_numbers.push_back(Square_Number(half_palindrome + '0' + reverse_half_palindrome));
                fair_and_square_numbers.push_back(Square_Number(half_palindrome + '1' + reverse_half_palindrome));

                // If we have two or fewer 1s, we can afford a 2 as the middle digit
                if (number_of_ones <= 2)
                {
                    fair_and_square_numbers.push_back(Square_Number(half_palindrome + '2' + reverse_half_palindrome));
                }
            } while (std::next_permutation(half_palindrome.begin(), half_palindrome.end()));
        }

        // Manages cases starting with 2
        half_palindrome.replace(half_palindrome.begin(), half_palindrome.end(), root_number, '0');
        half_palindrome[0] = '2';
        reverse_half_palindrome.resize(root_number);
        std::reverse_copy(half_palindrome.begin(), half_palindrome.end(), reverse_half_palindrome.begin());

        // Generate candidates
        fair_and_square_numbers.push_back(Square_Number(half_palindrome + reverse_half_palindrome));
        fair_and_square_numbers.push_back(Square_Number(half_palindrome + '0' + reverse_half_palindrome));
        fair_and_square_numbers.push_back(Square_Number(half_palindrome + '1' + reverse_half_palindrome));
    }

    std::sort(fair_and_square_numbers.begin(), fair_and_square_numbers.end(), Compare_Numbers);
    std::cout << "\nFair and square numbers generated.\n";
}

void QR_2013::Solve_Fair_and_Square(std::istream& input_stream, std::ostream& output_stream)
{
    unsigned int nb_tests = 0;
    unsigned int count_numbers = 0;
    std::string range_min;
    std::string range_max;

    if (fair_and_square_numbers.empty())
    {
        Generate_Fair_and_Square_Numbers();
    }

#ifdef _DEBUG
    // Displays the fair and square numbers
    /*for (const auto& number : fair_and_square_numbers)
    {
        std::cout << number << '\n';
    }*/
#endif

    input_stream >> nb_tests;
    for (unsigned int test_case = 1; test_case <= nb_tests; ++test_case)
    {
        input_stream >> range_min >> range_max;

        output_stream << "Case #" << test_case << ": ";

        count_numbers = Count_Numbers_In_Range(range_min, range_max);

        output_stream << count_numbers << '\n';
    }
}
