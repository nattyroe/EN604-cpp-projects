#pragma once
#include "../Base/ttt-base.hpp"

class Opponent : public TTTBase
{
public:
    bool chooseMove(char *board, int rows, int cols);
    int getRow();
    int getColumn();

private:
    int row = 0;
    int column = 0;
    bool attack();
    bool defend();
    bool selectRandom();
    void printCurrentGameBoard();
};