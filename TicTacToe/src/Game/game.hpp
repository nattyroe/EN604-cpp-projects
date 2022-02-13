#pragma once
#include "../Opponent/opponent.hpp"

/// @file
/// @author Nathan Roe
/// Main Game Object for Tic-Tac-Toe
///
/// Player plays as 'X' and enters moves in the form "# #"
/// for the row, column of their move, and the software
/// plays as 'O'.
class Game
{
public:
    /// Enumeration of Game States
    ///
    /// Player - Player Win
    /// Opponent - Opponent Win
    /// Tie - Board filled in with no win
    /// Ongoing - Incomplete Game
    enum class GameResultType
    {
        Player,
        Opponent,
        Tie,
        Ongoing
    };

    /// Run Main Gameplay Loop
    ///
    /// Runs a set of moves from player/opponent, and evaluates
    /// gamestate. Print results when game is complete
    void playGame();

    /// Check the status of a Game Board
    ///
    /// Checks to see the current status of a 3x3 matrix, to
    /// Evaluate if there is a winner (Player or Opponent), a tie,
    /// or an incomplete game.
    ///
    /// @param *board - pointer to 3x3 char matrix
    /// @param rows - number of rows in the board
    /// @param col - number of columns in the board
    /// @return the game result of type Game::GameResultType
    static GameResultType checkGameResult(char *board, int rows, int cols);

    /// Getter for the current 3x3 Game Board matrix
    char *getBoard();

    /// Print out current Game Board with Xs and Os
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

    /// Run a round of turns.
    ///
    /// Runs Player turn, and if game is not finished, runs the
    /// Opponent turn.
    void playRound();

    /// Runs Player Turn
    ///
    /// Accepts input for row and column for player moves in the
    /// form "# #" for <row column>. Input parsing is based on
    /// https://www.geeksforgeeks.org/extract-integers-string-c/
    void takePlayerTurn();

    /// Runs Opponent Turn
    ///
    /// Opponent evaluates current board, and the game grabs
    /// results and places opponent 'O'
    void takeOpponentTurn();
};