rm -f *.o
rm -f StatisticsTest

g++ -c src/IndependentProbability/independent-probability.cpp
g++ independent-probability.o src/probability-test.cpp -o ProbabilityTest
