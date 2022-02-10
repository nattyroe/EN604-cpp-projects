#include "game.hpp"

using namespace std;

void Game::playGame()
{
    do
    {
        takeTurn();
        this->gameResult = checkGameResult(this->board);
    } while (this->gameResult == Game::GameResultType::Ongoing);
}

Game::GameResultType Game::checkGameResult(char board[3][3])
{
    return Game::GameResultType::Ongoing;
}

char *Game::getBoard()
{
    return *this->board;
}

void Game::takeTurn()
{
    takePlayerTurn();
    this->gameResult = checkGameResult(this->board);
    if (Game::GameResultType::Ongoing == this->gameResult)
    {
        takeOpponentTurn();
    }
}
void Game::takePlayerTurn()
{
}
void Game::takeOpponentTurn()
{
}