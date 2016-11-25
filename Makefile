CXXFLAGS += -O2 -std=c++11 -Wall

all: main.o math.o film.o camera.o sphere.o scene.o
	g++ main.o math.o film.o camera.o sphere.o scene.o

clean:
	rm -f *.o *.out *.ppm
