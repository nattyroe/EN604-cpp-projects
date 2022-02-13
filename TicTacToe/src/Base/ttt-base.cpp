#include "ttt-base.hpp"
#include <iostream>

using namespace std;

void TTTBase::printCurrentGameBoard()
{
    cout << "\nCurrent Board:" << endl;
    cout << this->board[0][0] << "|" << this->board[0][1] << "|" << this->board[0][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[1][0] << "|" << this->board[1][1] << "|" << this->board[1][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[2][0] << "|" << this->board[2][1] << "|" << this->board[2][2] << "\n"
         << endl;
}

TTTBase::GameResultType TTTBase::checkGameResult(char *board, int rows, int cols)
{
    // Check Rows
    for (int row = 0; row < rows; ++row)
    {
        char *rowLoc = board + (row * cols);
        if (*(rowLoc + 0) == *(rowLoc + 1) &&
            *(rowLoc + 1) == *(rowLoc + 2))
        {
            if (*(board + (row * cols) + 0) == 'X')
            {
                cout << "Row" << endl;
                return TTTBase::GameResultType::Player;
            }
            else if (*(board + (row * cols) + 0) == 'O')
            {
                cout << "Row" << endl;
                return TTTBase::GameResultType::Opponent;
            }
        }
    }

    // Check Columns
    for (int col = 0; col < cols; ++col)
    {
        char *colLoc = board + col;
        if (*(colLoc + (0 * cols)) == *(colLoc + (1 * cols)) &&
            *(colLoc + (1 * cols)) == *(colLoc + (2 * cols)))
        {
            if (*(board + (0 * cols) + col) == 'X')
            {
                cout << "Column" << endl;
                return TTTBase::GameResultType::Player;
            }
            else if (*(board + (0 * cols) + col) == 'O')
            {
                cout << "Column" << endl;
                return TTTBase::GameResultType::Opponent;
            }
        }
    }

    // Check Diagonals
    if ((*(board + (0 * cols) + 0) == *(board + (1 * cols) + 1) &&
         *(board + (1 * cols) + 1) == *(board + (2 * cols) + 2)) ||
        (*(board + (0 * cols) + 2) == *(board + (1 * cols) + 1) &&
         *(board + (1 * cols) + 1) == *(board + (2 * cols) + 0)))
    {
        if (*(board + (1 * cols) + 1) == 'X')
        {
            return TTTBase::GameResultType::Player;
        }
        else if (*(board + (1 * cols) + 1) == 'O')
        {
            return TTTBase::GameResultType::Opponent;
        }
    }

    return TTTBase::GameResultType::Ongoing;
}