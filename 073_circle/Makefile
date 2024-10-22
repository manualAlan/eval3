CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++98

all: circles

circles: main.o point.o circle.o
	$(CXX) $(CXXFLAGS) -o circles main.o point.o circle.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

point.o: point.cpp point.hpp
	$(CXX) $(CXXFLAGS) -c point.cpp

circle.o: circle.cpp circle.hpp
	$(CXX) $(CXXFLAGS) -c circle.cpp

clean:
	rm -f *.o circles
