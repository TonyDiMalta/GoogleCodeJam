#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "2013/QualificationRound/Qualification-Round.hpp"

const std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> list_valid_entries
{
    { "QR_2013",
        { "Qualification Round 2013",
            {
                { "T4", "Tic-Tac-Toe-Tomek" },
                { "FS", "Fair and Square" }
            }
        }
    }
};

bool Is_Valid_Entry(const std::string& chosen_entry, const std::string& chosen_problem = "")
{
    const auto& entry_it = list_valid_entries.find(chosen_entry);

    if (entry_it == list_valid_entries.end())
    {
        return false;
    }

    if (chosen_problem.empty())
    {
        return true;
    }

    const auto& entry_values = list_valid_entries.at(chosen_entry).second;
    
    if (entry_values.find(chosen_problem) == entry_values.end())
    {
        return false;
    }

    return true;
}

void Display_Valid_Entries(const std::string& chosen_entry = "")
{
    if (chosen_entry.empty())
    {
        for (const auto& entry : list_valid_entries)
        {
            std::cout << '[' << entry.first << "] " << entry.second.first << '\n';
        }
    }
    else
    {
        for (const auto& entry : list_valid_entries)
        {
            if (chosen_entry == entry.first)
            {
                const auto& to_parse = entry.second.second;
                for (const auto& values : to_parse)
                {
                    std::cout << '[' << values.first << "] " << values.second << '\n';
                }
            }
        }
    }
}

std::string Get_Directory(const std::string& my_namespace)
{
    if (my_namespace == "QR_2013")
    {
        return QR_2013::directory_path;
    }

    std::cerr << "No namespace \"" << my_namespace << "\" found.\n";
    return std::string();
}

void Function_To_Call(const std::string& my_namespace, const std::string& my_function, std::ifstream& file_input, std::ofstream& file_output)
{
    if (my_namespace == "QR_2013")
    {
        if (my_function == "T4")
        {
            QR_2013::Solve_T4(file_input, file_output);
        }
        else if (my_function == "FS")
        {
            QR_2013::Solve_FS(file_input, file_output);
        }
        else
        {
            std::cerr << "No function \"" << my_function << "\" to call.\n";
        }
    }
    else
    {
        std::cerr << "No namespace \"" << my_namespace << "\" found.\n";
    }
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
            Display_Valid_Entries(chosen_entry);
        }
        else if (Is_Valid_Entry(chosen_entry, user_input))
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
