#include <iostream>

#include "ray.h"
#include "math.h"
#include "film.h"
#include "vector3.h"

using namespace gui;

Vector3 color(const Ray& ray) {
	float k = (ray.direction.y + 1) * 0.5f;
	return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
}

int main() {
	Film film;

	float u, v;
	for(int i = 0; i < film.height; ++i) {
		v = 1 - (float) i / film.height * 2;
		for(int j = 0; j < film.width; ++j) {
			u = (float) j / film.height * 2 - 2;
			Ray ray = Ray(Vector3(0), Vector3(u, v, -1));
			film.pixels[i][j] = color(ray);
		}
	}

	film.gammaCorrection();
	film.writePPM();

	return 0;
}
