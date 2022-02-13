#include "opponent.hpp"
#include <iostream>

using namespace std;

bool Opponent::chooseMove(char *board, int rows, int cols)
{
    if (!(rows == BOARD_SIZE) or !(cols == BOARD_SIZE))
    {
        return false;
    }

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            cout << *(board + (row * cols) + col) << endl;
            this->board[row][col] = *(board + (row * cols) + col);
        }
    }

    bool moveChosen = false;

    moveChosen = attack();
    if (!moveChosen)
    {
        moveChosen = defend();
    }
    if (!moveChosen)
    {
        moveChosen = selectRandom();
    }

    return moveChosen;
}

bool Opponent::attack()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                this->board[row][col] = 'O';
                GameResultType result;
                result == checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == GameResultType::Opponent)
                {
                    this->row = row;
                    this->column = col;
                    cout << "Attacking" << endl;
                    return true;
                }
                else
                {
                    this->board[row][col] = EMPTY;
                }
            }
        }
    }
    return false;
}

bool Opponent::defend()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                this->board[row][col] = 'X';
                GameResultType result;
                result == checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == GameResultType::Player)
                {
                    this->board[row][col] = 'O';
                    this->row = row;
                    this->column = col;
                    cout << "Defending" << endl;
                    return true;
                }
                else
                {
                    this->board[row][col] = EMPTY;
                }
            }
        }
    }
    return false;
}

bool Opponent::selectRandom()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                this->row = row;
                this->column = col;
                this->board[row][col] = 'O';
                cout << "Choosing Randomly" << endl;
                return true;
            }
        }
    }
    return false;
}