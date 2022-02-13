#pragma once

class Opponent
{
public:
    /// Selects move based on a Game Board
    ///
    /// Evaluates the current status of a 3x3 matrix to
    /// select the location of the Opponent's next move
    ///
    /// @param *board - pointer to 3x3 char matrix
    /// @param rows - number of rows in the board
    /// @param col - number of columns in the board
    /// @return a boolean of whether a valid move was found
    bool chooseMove(char *board, int rows, int cols);

    /// Gets the selected row for the Opponent's next move
    ///
    /// @return an int of the Opponent's chosen row
    int getRow();

    /// Gets the selected column for the Opponent's next move
    ///
    /// @return an int of the Opponent's chosen column
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

    /// Search for possible winning moves
    ///
    /// Tests move locations to see if any will win game
    bool attack();

    /// Search for possible Player winning moves
    ///
    /// Tests move locations to see if any spaces will
    /// win for the player, and block that move
    bool defend();

    /// Seaches for first open space
    bool selectRandom();
};