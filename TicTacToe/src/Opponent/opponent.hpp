#pragma once

class Opponent
{
public:
    bool chooseMove(char *board, int rows, int cols);
    int getRow();
    int getColumn();

private:
    int row = 0;
    int column = 0;
    const int BOARD_SIZE = 3;
    const char EMPTY = ' ';
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    bool attack();
    bool defend();
    bool selectRandom();
    void printCurrentGameBoard();
};