rm -f *.o
rm -f PlayTicTacToe

g++ -c src/Game/game.cpp
g++ -c src/Opponent/opponent.cpp
#g++ -c src/Base/ttt-base.cpp
#g++ game.o opponent.o ttt-base.o src/play-tic-tac-toe.cpp  -o PlayTicTacToe
g++ game.o opponent.o src/play-tic-tac-toe.cpp -o PlayTicTacToe
