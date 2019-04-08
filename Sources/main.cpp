#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

#include "2013/QualificationRound/Qualification-Round-2013.hpp"
#include "2014/QualificationRound/Qualification-Round-2014.hpp"
#include "2015/QualificationRound/Qualification-Round-2015.hpp"

typedef void(*function_pointer)(std::istream&, std::ostream&);

const std::map<std::string, std::tuple<std::string, std::string, std::map<std::string, std::pair<std::string, function_pointer>>>> list_valid_entries
{
    { "QR_2013",
        { "Qualification Round 2013", QR_2013::directory_path,
            {
                { "T4",
                    { "Tic-Tac-Toe-Tomek", QR_2013::Solve_T4 }
                },
                { "Lm",
                    { "Lawnmower", QR_2013::Solve_Lm }
                },
                { "FS",
                    { "Fair and Square", QR_2013::Solve_FS }
                }
            }
        }
    },
    { "QR_2014",
        { "Qualification Round 2014", QR_2014::directory_path,
            {
                { "MT",
                    { "Magic Trick", QR_2014::Solve_MT }
                },
                { "CA",
                    { "Cookie Clicker Alpha", QR_2014::Solve_CA }
                },
                { "DW",
                    { "Deceitful War", QR_2014::Solve_DW }
                }
            }
        }
    },
    { "QR_2015",
        { "Qualification Round 2015", QR_2015::directory_path,
            {
                { "SO",
                    { "Standing Ovation", QR_2015::Solve_SO }
                }
            }
        }
    }
};

bool Is_Valid_Entry(const std::string& chosen_entry, bool should_display_error = true)
{
    const auto& entry_it = list_valid_entries.find(chosen_entry);

    if (entry_it == list_valid_entries.end())
    {
        if (should_display_error)
        {
            std::cerr << "No entry \"" << chosen_entry << "\" found.\n";
        }
        return false;
    }

    return true;
}

bool Is_Valid_Problem(const std::string& chosen_entry, const std::string& chosen_problem, bool should_display_error = true)
{
    if (!Is_Valid_Entry(chosen_entry, should_display_error))
    {
        return false;
    }

    const auto& problem_values = std::get<2>(list_valid_entries.at(chosen_entry));
    const auto& problem_it = problem_values.find(chosen_problem);

    if (problem_it == problem_values.end())
    {
        if (should_display_error)
        {
            std::cerr << "No problem \"" << chosen_problem << "\" found.\n";
        }
        return false;
    }

    return true;
}

void Display_Valid_Entries()
{
    for (const auto& entry : list_valid_entries)
    {
        std::cout << '[' << entry.first << "] " << std::get<0>(entry.second) << '\n';
    }
}

void Display_Valid_Problems(const std::string& chosen_entry)
{
    if (!Is_Valid_Entry(chosen_entry))
    {
        return;
    }

    const auto& problem_values = std::get<2>(list_valid_entries.at(chosen_entry));

    for (const auto& problem : problem_values)
    {
        std::cout << '[' << problem.first << "] " << std::get<0>(problem.second) << '\n';
    }
}

std::string Get_Directory(const std::string& my_namespace)
{
    if (!Is_Valid_Entry(my_namespace))
    {
        std::cerr << "No namespace \"" << my_namespace << "\" found.\n";
        return std::string();
    }

    return std::get<1>(list_valid_entries.at(my_namespace));
}

void Function_To_Call(const std::string& my_namespace, const std::string& my_function, std::istream& file_input, std::ostream& file_output)
{
    if (!Is_Valid_Problem(my_namespace, my_function, true))
    {
        return;
    }

    const auto& problem_values = std::get<2>(list_valid_entries.at(my_namespace));
    const auto& function_to_call = std::get<1>(problem_values.at(my_function));

    if (function_to_call == nullptr)
    {
        std::cerr << "No function \"" << my_function << "\" found.\n";
        return;
    }

    function_to_call(file_input, file_output);
}

int main()
{
    std::string user_input;
    std::string chosen_entry;
    std::string chosen_problem;
    std::string directory_path;
    std::ifstream file_input;
    file_input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::ofstream file_output;
    file_output.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    std::cout << "Enter \"quit\" to leave.\n";
    std::cout << "Enter \"help\" to get a list of possible entries.\n";

    while (chosen_entry.empty())
    {
        std::cout << "\nPlease enter a valid entry (e.g. QR_2013 for Qualif. Round 2013) : ";
        std::getline(std::cin, user_input);

        if (user_input == "quit")
        {
            return 0;
        }

        if (user_input == "help")
        {
            Display_Valid_Entries();
        }
        else if (Is_Valid_Entry(user_input))
        {
            directory_path = Get_Directory(user_input);
            chosen_entry = user_input;
        }
    }

    while (chosen_problem.empty())
    {
        std::cout << "\nPlease enter a problem to solve (e.g. FS for Fair and Square) : ";
        std::getline(std::cin, user_input);

        if (user_input == "quit")
        {
            return 0;
        }

        if (user_input == "help")
        {
            Display_Valid_Problems(chosen_entry);
        }
        else if (Is_Valid_Problem(chosen_entry, user_input))
        {
            chosen_problem = user_input;
        }
    }

    do
    {
        std::cout << "\nPlease enter a valid file name [.in] (e.g. Small-test[.in]) : ";
        std::getline(std::cin, user_input);

        if (user_input == "quit")
        {
            return 0;
        }

        if (user_input.size() > 3 && user_input.substr(user_input.size() - 3).compare(".in") == 0)
        {
            user_input.erase(user_input.end() - 3, user_input.end());
        }
        
        try
        {
            file_input.open(directory_path + user_input + ".in", std::ios::in);

            try
            {
                file_output.open(directory_path + user_input + ".out", std::ios::trunc | std::ios::out);
            }
            catch (const std::ofstream::failure& e)
            {
                std::cerr << "Exception opening/creating output file, please try again.\n";
#ifdef _DEBUG
                std::cerr << "Exception caught : " << e.what() << '\n';
#endif
            }
        }
        catch (const std::ifstream::failure& e)
        {
            std::cerr << "Exception opening/reading input file, please try again.\n";
#ifdef _DEBUG
            std::cerr << "Exception caught : " << e.what() << '\n';
#endif
        }

    } while (!file_input || !file_output);

    Function_To_Call(chosen_entry, chosen_problem, file_input, file_output);

    file_input.close();
    file_output.close();

    return 0;
}
