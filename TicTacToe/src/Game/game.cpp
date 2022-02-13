#include "game.hpp"
#include <iostream>
#include <sstream>

using namespace std;

void Game::playGame()
{
    do
    {
        printCurrentGameBoard();
        playRound();
        this->gameResult = checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
    } while (this->gameResult == Game::GameResultType::Ongoing);

    printCurrentGameBoard();

    switch (this->gameResult)
    {
    case Game::GameResultType::Player:
        cout << "You Win!" << endl;
        break;
    case Game::GameResultType::Opponent:
        cout << "You Lose!" << endl;
        break;
    default:
        cout << "It's a Tie." << endl;
        break;
    }
}

void Game::printCurrentGameBoard()
{
    cout << "\nCurrent Board:" << endl;
    cout << this->board[0][0] << "|" << this->board[0][1] << "|" << this->board[0][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[1][0] << "|" << this->board[1][1] << "|" << this->board[1][2] << endl;
    cout << "_ _ _" << endl;
    cout << this->board[2][0] << "|" << this->board[2][1] << "|" << this->board[2][2] << "\n"
         << endl;
}

Game::GameResultType Game::checkGameResult(char *board, int rows, int cols)
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
                return Game::GameResultType::Player;
            }
            else if (*(board + (row * cols) + 0) == 'O')
            {
                return Game::GameResultType::Opponent;
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
                return Game::GameResultType::Player;
            }
            else if (*(board + (0 * cols) + col) == 'O')
            {
                return Game::GameResultType::Opponent;
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
            return Game::GameResultType::Player;
        }
        else if (*(board + (1 * cols) + 1) == 'O')
        {
            return Game::GameResultType::Opponent;
        }
    }

    // Check For Tie
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (' ' == *(board + (row * cols) + col))
            {
                return Game::GameResultType::Ongoing;
            }
        }
    }
    return Game::GameResultType::Tie;
}

char *Game::getBoard()
{
    return *this->board;
}

void Game::playRound()
{
    takePlayerTurn();
    this->gameResult = checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
    if (Game::GameResultType::Ongoing == this->gameResult)
    {
        takeOpponentTurn();
    }
}

// https://www.geeksforgeeks.org/extract-integers-string-c/
void Game::takePlayerTurn()
{
    while (true)
    {
        int row, column;
        cout << "Your Move: ";
        string result;
        getline(cin, result);
        if (!(result.length() == 3))
        {
            cout << "Please Submit Your move in the form <row column>, i.e.:" << endl;
            cout << "1 2" << endl;
            continue;
        }
        else
        {
            stringstream ss;
            ss << result;
            string temp;
            int found[2] = {0, 0};
            int loc = 0;
            while (!ss.eof())
            {
                ss >> temp;
                if (stringstream(temp) >> found[loc])
                {
                    ++loc;
                }
            }
            row = found[0];
            column = found[1];
        }

        if (row <= 0 || row > BOARD_SIZE ||
            column <= 0 || column > BOARD_SIZE)
        {
            cout << "Make sure your values are between 1 and 3." << endl;
        }
        else
        {
            if (!(this->board[row - 1][column - 1] == EMPTY))
            {
                cout << "That Space is already Played." << endl;
            }
            else
            {
                this->board[row - 1][column - 1] = 'X';
                break;
            }
        }
    }
}

void Game::takeOpponentTurn()
{
    cout << "Opponent Turn" << endl;
    bool result = false;
    result = this->opponent->chooseMove(*this->board, BOARD_SIZE, BOARD_SIZE);

    if (result)
    {
        int row, col = 0;
        row = this->opponent->getRow();
        col = this->opponent->getColumn();
        this->board[row][col] = 'O';
    }
}