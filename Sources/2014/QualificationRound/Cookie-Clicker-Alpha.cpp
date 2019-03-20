#include <fstream>
#include <iomanip>

#include "Qualification-Round-2014.hpp"

constexpr double cookies_per_second = 2.0;
constexpr unsigned int decimal_precision = 7;

double Minimum_Time_To_Generate_Cookies(double farm_cost, double farm_cookies_per_second, double cookies_required)
{
    double build_time = farm_cost / cookies_per_second;
    double time_to_make_cookies = cookies_required / cookies_per_second;
    double time_to_farm_cookies = cookies_required / (cookies_per_second + farm_cookies_per_second);
    double time_spent_building = 0;
    unsigned int nb_buildings;

    // While making cookies takes longer than building a farm and making it fruitful, build a new farm
    for (nb_buildings = 1; time_to_make_cookies > build_time + time_to_farm_cookies; ++nb_buildings)
    {
        // Sum the construction times of the farms
        time_spent_building += build_time;
        // Recalculate the time needed to build a new farm
        build_time = farm_cost / (cookies_per_second + farm_cookies_per_second * nb_buildings);
        // Recalculate the time needed to make cookies
        time_to_make_cookies = cookies_required / (cookies_per_second + farm_cookies_per_second * nb_buildings);
        // Recalculate the time needed to farm cookies with an extra building
        time_to_farm_cookies = cookies_required / (cookies_per_second + farm_cookies_per_second * (nb_buildings + 1));
    }

    // Time spent building farms and making cookies
    return time_spent_building + time_to_make_cookies;
}

void QR_2014::Solve_CA(std::ifstream& file_input, std::ofstream& file_output)
{
    unsigned int nb_cases;
    unsigned int index;
    double farm_cost;
    double farm_cookies_per_second;
    double cookies_required;
    double time_to_make_cookies;

    file_input >> nb_cases;
    for (index = 1; index <= nb_cases; ++index)
    {
        file_output << "Case #" << index << ": ";

        file_input >> farm_cost >> farm_cookies_per_second >> cookies_required;

        time_to_make_cookies = Minimum_Time_To_Generate_Cookies(farm_cost, farm_cookies_per_second, cookies_required);
        
        file_output << std::fixed << std::setprecision(decimal_precision) << time_to_make_cookies << '\n';
    }
}
