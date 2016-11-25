CXXFLAGS += -O2 -std=c++11 -Wall

all: main.o math.o film.o camera.o
	g++ main.o math.o film.o camera.o

clean:
	rm *.o *.out *.ppm
