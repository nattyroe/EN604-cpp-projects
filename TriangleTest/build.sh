rm -f *.o
rm -f TriangleTest

g++ -c src/Triangle/triangle.cpp
g++ triangle.o src/triangle-test.cpp  -o TriangleTest
