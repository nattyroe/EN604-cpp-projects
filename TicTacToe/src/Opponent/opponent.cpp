#include "opponent.hpp"
#include "../Game/game.hpp"
#include <iostream>

using namespace std;

int Opponent::getRow()
{
    return this->row;
}

int Opponent::getColumn()
{
    return this->column;
}

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

void Opponent::printCurrentGameBoard()
{
    cout << "\nCurrent Board:" << endl;
    cout << this->board[0][0] << "|" << this->board[0][1] << "|" << this->board[0][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[1][0] << "|" << this->board[1][1] << "|" << this->board[1][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[2][0] << "|" << this->board[2][1] << "|" << this->board[2][2] << "\n"
         << endl;
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
                Game::GameResultType result;
                result = Game::checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == Game::GameResultType::Opponent)
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
                Game::GameResultType result;
                result = Game::checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == Game::GameResultType::Player)
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