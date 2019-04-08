#include <iostream>
#include <map>
#include <string>

#include "Qualification-Round-2013.hpp"

constexpr unsigned int BOARD_SIZE = 4;

enum T4_Output_Type
{
    NOT_OVER,
    DRAW,
    O_WON,
    X_WON
};

const static std::map<T4_Output_Type, std::string> T4_Output =
{
    { NOT_OVER, "Game has not completed" },
    { DRAW, "Draw" },
    { O_WON, "O won" },
    { X_WON, "X won" }
};

struct Symbols_Number
{
    unsigned int line = 0;
    unsigned int column = 0;
    unsigned int diagonal1 = 0;
    unsigned int diagonal2 = 0;
};

void Increment_Matching_Number(const char& current_char, unsigned int& number_X, unsigned int& number_O) noexcept
{
    if (current_char == 'X')
    {
        ++number_X;
    }
    else if (current_char == 'O')
    {
        ++number_O;
    }
    else if (current_char == 'T')
    {
        ++number_X;
        ++number_O;
    }
}

T4_Output_Type Check_Game_State(std::string (&game_board)[BOARD_SIZE])
{
    bool is_board_full = true;
    Symbols_Number player_X;
    Symbols_Number player_O;

    for (unsigned int index1 = 0; index1 < BOARD_SIZE; ++index1)
    {
        player_X.line = 0;
        player_X.column = 0;
        player_O.line = 0;
        player_O.column = 0;

        if (is_board_full &&
            game_board[index1].find('.') != std::string::npos)
        {
            is_board_full = false;
        }

        for (unsigned int index2 = 0; index2 < BOARD_SIZE; ++index2)
        {
            Increment_Matching_Number(game_board[index1][index2], player_X.line, player_O.line);
            Increment_Matching_Number(game_board[index2][index1], player_X.column, player_O.column);
        }

        if (player_X.line == BOARD_SIZE ||
            player_X.column == BOARD_SIZE)
        {
            return T4_Output_Type::X_WON;
        }

        if (player_O.line == BOARD_SIZE ||
            player_O.column == BOARD_SIZE)
        {
            return T4_Output_Type::O_WON;
        }

        Increment_Matching_Number(game_board[index1][index1], player_X.diagonal1, player_O.diagonal1);
        Increment_Matching_Number(game_board[index1][BOARD_SIZE - index1 - 1], player_X.diagonal2, player_O.diagonal2);
    }

    if (player_X.diagonal1 == BOARD_SIZE ||
        player_X.diagonal2 == BOARD_SIZE)
    {
        return T4_Output_Type::X_WON;
    }

    if (player_O.diagonal1 == BOARD_SIZE ||
        player_O.diagonal2 == BOARD_SIZE)
    {
        return T4_Output_Type::O_WON;
    }
    
    if (is_board_full)
    {
        return T4_Output_Type::DRAW;
    }
    
    return T4_Output_Type::NOT_OVER;
}

void QR_2013::Solve_T4(std::istream& file_input, std::ostream& file_output)
{
    unsigned int nb_boards = 0;
    std::string game_board[BOARD_SIZE];
    T4_Output_Type game_state = T4_Output_Type::NOT_OVER;

    file_input >> nb_boards;
    for (unsigned int board_index = 1; board_index <= nb_boards; ++board_index)
    {
        for (auto& line : game_board)
        {
            file_input >> line;
        }

        file_output << "Case #" << board_index << ": ";

        game_state = Check_Game_State(game_board);

        file_output << T4_Output.at(game_state) << '\n';
    }
}
