rm -f *.o
rm -f PokerHandTest

g++ -c src/Hand/card.cpp
g++ -c src/Hand/hand.cpp
g++ hand.o card.o src/poker-hand-test.cpp -o PokerHandTest
