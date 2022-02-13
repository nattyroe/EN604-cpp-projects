#include "game.hpp"
#include <iostream>
#include <sstream>

using namespace std;

void Game::playGame()
{
    do
    {
        printCurrentGameBoard();
        takeTurn();
        this->gameResult = checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
    } while (this->gameResult == GameResultType::Ongoing);
}

char *Game::getBoard()
{
    return *this->board;
}

void Game::takeTurn()
{
    takePlayerTurn();
    this->gameResult = checkGameResult(*this->board, BOARD_SIZE, BOARD_SIZE);
    if (GameResultType::Ongoing == this->gameResult)
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
                printCurrentGameBoard();
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