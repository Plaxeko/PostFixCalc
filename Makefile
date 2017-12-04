calc: BigInt.o
    g++ -stdc++11 -o calc calc.cpp BigInt.o
BigInt.o: BigInt.cpp
    g++ -std=c++11 -c BigInt.cpp -o BigInt.o


