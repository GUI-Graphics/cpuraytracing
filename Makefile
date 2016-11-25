CXXFLAGS += -O2 -std=c++11 -Wall

all: main.o math.o film.o
	g++ main.o math.o film.o
