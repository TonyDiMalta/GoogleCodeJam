#ifndef QUALIFICATION_ROUND_2013
#define QUALIFICATION_ROUND_2013

#include <fstream>
#include <string>

namespace QR_2013
{
    static const std::string directory_path = "Sources/2013/QualificationRound/";
    void Solve_T4(std::ifstream& file_input, std::ofstream& file_output);
    void Solve_Lm(std::ifstream& file_input, std::ofstream& file_output);
    void Solve_FS(std::ifstream& file_input, std::ofstream& file_output);
}

#endif // QUALIFICATION_ROUND_2013
