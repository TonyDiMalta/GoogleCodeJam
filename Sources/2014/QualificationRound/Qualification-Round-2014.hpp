#ifndef QUALIFICATION_ROUND_2014
#define QUALIFICATION_ROUND_2014

#include <fstream>
#include <string>

namespace QR_2014
{
    static std::string directory_path = "Sources/2014/QualificationRound/";
    void Solve_MT(std::ifstream& file_input, std::ofstream& file_output);
    void Solve_CA(std::ifstream& file_input, std::ofstream& file_output);
}

#endif // QUALIFICATION_ROUND_2014
