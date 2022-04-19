make:
	g++ main.cpp `wx-config --cxxflags --libs std` -o main
	g++ app.cpp `wx-config --cxxflags --libs std` -o client
run:
	./main