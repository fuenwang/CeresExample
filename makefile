all:
	g++ -O3 hello.cpp -lceres -lglog -std=c++11
	./a.out
