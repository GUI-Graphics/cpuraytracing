CXXFLAGS += -O2 -std=c++11 -Wall

all: main.o math.o film.o camera.o sphere.o scene.o diffuse.o metal.o dielectric.o renderer.o
	g++ main.o math.o film.o camera.o sphere.o scene.o diffuse.o metal.o dielectric.o renderer.o

clean:
	rm -f *.o *.out *.ppm
