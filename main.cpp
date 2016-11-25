#include <iostream>

#include "ray.h"
#include "math.h"
#include "film.h"
#include "camera.h"
#include "vector3.h"

using namespace gui;

Vector3 color(const Ray& ray) {
	float k = (ray.direction.y + 1) * 0.5f;
	return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
}

int main() {
	Film film;
	Camera camera(film);

	for(int i = 0; i < film.height; ++i) {
		printf("\rrendering %5.2f%%", 100.0f * (i + 1) / film.height);
		for(int j = 0; j < film.width; ++j) {
			Ray ray = camera.getRay(j, i);
			film.pixels[i][j] = color(ray);
		}
	}

	printf("\n");

	film.gammaCorrection();
	film.writePPM();

	return 0;
}
