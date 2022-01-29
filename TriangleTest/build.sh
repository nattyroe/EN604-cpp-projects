rm -f *.o
rm -f TriangleTest

g++ -c Triangle/triangle.cpp
g++ triangle.o TriangleTest.cpp  -o TriangleTest
