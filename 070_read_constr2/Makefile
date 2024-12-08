CXX = g++
CXXFLAGS = -Wall -g

EXEC = code

all: $(EXEC)

$(EXEC): code.cpp code.h
	$(CXX) $(CXXFLAGS) -o $(EXEC) code.cpp

run: $(EXEC)
	./$(EXEC) > answer.txt

clean:
	rm -f $(EXEC) answer.txt
