#include "opponent.hpp"
#include "../Game/game.hpp"
#include <iostream>

using namespace std;

// Gets the selected row for the Opponent's next move
int Opponent::getRow()
{
    return this->row;
} // End function getRow

// Gets the selected column for the Opponent's next move
int Opponent::getColumn()
{
    return this->column;
} // End function getColumn

// Selects move based on a given Game Board
bool Opponent::chooseMove(char *board, int rows, int cols)
{
    // Verify the board is the correct size
    if (!(rows == BOARD_SIZE) or !(cols == BOARD_SIZE))
    {
        return false;
    }

    // Make a copy of the board
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            this->board[row][col] = *(board + (row * cols) + col);
        }
    }

    bool moveChosen = false;

    // Try to find a winning move
    moveChosen = attack();

    // If no winning moves, protect against a Player win
    if (!moveChosen)
    {
        moveChosen = defend();
    }

    // If player has no winning moves, select first open space
    if (!moveChosen)
    {
        moveChosen = selectRandom();
    }

    return moveChosen;
}

// Search for possible winning moves
bool Opponent::attack()
{
    // Iterate over board
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                // Test open spaces to see if they are winning placements
                this->board[row][col] = 'O';
                Game::GameResultType result;
                result = Game::checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == Game::GameResultType::Opponent)
                {
                    // If space wins, set selection
                    this->row = row;
                    this->column = col;
                    cout << "Attacking" << endl;
                    return true;
                }
                else
                {
                    // Return board to starting configuration
                    this->board[row][col] = EMPTY;
                }
            }
        }
    }
    return false;
} // End function attack

bool Opponent::defend()
{
    // Iterate over board
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                // Test open spaces to see if they are winning placements
                // for the player
                this->board[row][col] = 'X';
                Game::GameResultType result;
                result = Game::checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
                if (result == Game::GameResultType::Player)
                {
                    // If space wins for player, set selection to block
                    this->board[row][col] = 'O';
                    this->row = row;
                    this->column = col;
                    cout << "Defending" << endl;
                    return true;
                }
                else
                {
                    // Return board to starting configuration
                    this->board[row][col] = EMPTY;
                }
            }
        }
    }
    return false;
} // End function defend

bool Opponent::selectRandom()
{
    // Iterate over board
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (this->board[row][col] == EMPTY)
            {
                // If empty space is found, select space
                this->row = row;
                this->column = col;
                this->board[row][col] = 'O';
                cout << "Choosing Randomly" << endl;
                return true;
            }
        }
    }
    return false;
} // End function selectRandom