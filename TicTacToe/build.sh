rm -f *.o
rm -f PlayTicTacToe

g++ -c src/Game/game.cpp
g++ -c src/Opponent/opponent.cpp
g++ game.o opponent.o src/play-tic-tac-toe.cpp -o PlayTicTacToe
