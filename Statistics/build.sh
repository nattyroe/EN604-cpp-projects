rm -f *.o
rm -f StatisticsTest

g++ -c src/Statistic/statistic.cpp
g++ statistic.o src/statistic-test.cpp -o StatisticTest
