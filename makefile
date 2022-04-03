make:
	g++ main.cpp `wx-config --cxxflags --libs std` -o main
run:
	./program