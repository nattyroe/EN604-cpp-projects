#pragma once

class TTTBase
{
public:
    enum class GameResultType
    {
        Player,
        Opponent,
        Tie,
        Ongoing
    };
    void printCurrentGameBoard();
    static GameResultType checkGameResult(char *board, int rows, int cols);

protected:
    const int BOARD_SIZE = 3;
    const char EMPTY = ' ';
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
};
