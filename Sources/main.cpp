#include <fstream>
#include <iostream>
#include <string>

#include "2013/QualificationRound/Qualification-Round.hpp"

int main()
{
    std::string file_to_read;
    std::ifstream file_input;
    file_input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::ofstream file_output;
    file_output.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    std::cout << "Enter \"quit\" to leave.\n";

    do
    {
        std::cout << "\nPlease enter a valid file name [.in] : ";
        std::getline(std::cin, file_to_read);
        if (file_to_read == "quit")
        {
            return 0;
        }

        if (file_to_read.substr(file_to_read.size() - 3).compare(".in") == 0)
        {
            file_to_read.erase(file_to_read.end() - 3, file_to_read.end());
        }
        
        try
        {
            file_input.open(QR_2013::directory_path + file_to_read + ".in", std::ios::in);

            try
            {
                file_output.open(QR_2013::directory_path + file_to_read + ".out", std::ios::trunc | std::ios::out);
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

    QR_2013::Solve_T4(file_input, file_output);

    file_input.close();
    file_output.close();

    return 0;
}
