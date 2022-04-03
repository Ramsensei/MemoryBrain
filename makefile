make:
	g++ main.cpp `wx-config --cxxflags --libs std` -o main
	g++ mainClient.cpp `wx-config --cxxflags --libs std` -o client
run:
	./main