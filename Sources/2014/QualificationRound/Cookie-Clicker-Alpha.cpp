#include <iomanip>
#include <iostream>

#include "Qualification-Round-2014.hpp"

constexpr double cookies_per_second = 2.0;
constexpr unsigned int decimal_precision = 7;

double Minimum_Time_To_Generate_Cookies(double farm_cost, double farm_cookies_per_second, double cookies_required) noexcept
{
    double build_time = 0;
    double time_to_make_cookies = 0;
    double time_to_farm_cookies = 0;
    double time_spent_building = 0;
    unsigned int nb_buildings = 0;

    do
    {
        // Sum the construction times of the farms
        time_spent_building += build_time;
        // Calculate the time needed to build a new farm
        build_time = farm_cost / (cookies_per_second + farm_cookies_per_second * nb_buildings);
        // Calculate the time needed to make cookies
        time_to_make_cookies = cookies_required / (cookies_per_second + farm_cookies_per_second * nb_buildings);
        // Calculate the time needed to farm cookies with an extra building
        time_to_farm_cookies = cookies_required / (cookies_per_second + farm_cookies_per_second * (++nb_buildings));
    // While making cookies takes longer than building a farm and making it fruitful, build a new farm
    } while (time_to_make_cookies > build_time + time_to_farm_cookies);

    // Time spent building farms and making cookies
    return time_spent_building + time_to_make_cookies;
}

void QR_2014::Solve_Cookie_Clicker_Alpha(std::istream& input_stream, std::ostream& output_stream)
{
    unsigned int nb_cases = 0;
    unsigned int index = 0;
    double farm_cost = 0;
    double farm_cookies_per_second = 0;
    double cookies_required = 0;
    double time_to_make_cookies = 0;

    input_stream >> nb_cases;
    for (index = 1; index <= nb_cases; ++index)
    {
        output_stream << "Case #" << index << ": ";

        input_stream >> farm_cost >> farm_cookies_per_second >> cookies_required;

        time_to_make_cookies = Minimum_Time_To_Generate_Cookies(farm_cost, farm_cookies_per_second, cookies_required);
        
        output_stream << std::fixed << std::setprecision(decimal_precision) << time_to_make_cookies << '\n';
    }
}
