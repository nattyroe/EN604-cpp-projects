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
    GameResultType checkGameResult(char board[3][3]);
    char *getBoard();
    void printCurrentGameBoard();

private:
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