CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall
LDFLAGS=-lraylib -lpthread -ldl
INCLUDES=-I ./include

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: main.out 

main.out: $(OBJ)
	echo $(LDFLAGS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(INCLUDES)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm *.o main.out

.PHONY: clean all
