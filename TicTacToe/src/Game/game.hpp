#pragma once
#include "../Base/ttt-base.hpp"
#include "../Opponent/opponent.hpp"

class Game : public TTTBase
{
public:
    void playGame();
    char *getBoard();

private:
    Opponent *opponent = new Opponent();
    GameResultType gameResult = GameResultType::Ongoing;

    void takeTurn();
    void takePlayerTurn();
    void takeOpponentTurn();
};