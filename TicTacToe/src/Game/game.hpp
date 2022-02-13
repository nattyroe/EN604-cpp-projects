#pragma once
#include "../Opponent/opponent.hpp"

class Game
{
public:
    enum class GameResultType
    {
        Player,
        Opponent,
        Tie,
        Ongoing
    };
    void playGame();
    static GameResultType checkGameResult(char *board, int rows, int cols);
    char *getBoard();
    void printCurrentGameBoard();

private:
    const int BOARD_SIZE = 3;
    const char EMPTY = ' ';
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    Opponent *opponent = new Opponent();
    GameResultType gameResult = GameResultType::Ongoing;

    void takeTurn();
    void takePlayerTurn();
    void takeOpponentTurn();
};