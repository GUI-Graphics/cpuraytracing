#include <iostream>

#include "ray.h"
#include "math.h"
#include "film.h"
#include "scene.h"
#include "sphere.h"
#include "camera.h"
#include "vector3.h"

using namespace gui;

Vector3 color(const Ray& ray, const Scene& scene) {
	Intersection intersection;
	if(scene.intersect(ray, 0, 10000, intersection)) {
		return Vector3(1);
	} else {
		float k = (ray.direction.y + 1) * 0.5f;
		return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
	}
}

void initScene(Scene& scene) {
	scene.shapes.push_back(new Sphere(Vector3(0, -1001, 0), 1000));
	scene.shapes.push_back(new Sphere(Vector3(0, 0.2f, -1), 0.2f));
}

int main() {
	Film film;
	Camera camera(film);

	Scene scene;
	initScene(scene);

	for(int i = 0; i < film.height; ++i) {
		printf("\rrendering %5.2f%%", 100.0f * (i + 1) / film.height);
		for(int j = 0; j < film.width; ++j) {
			for(int k = 0; k < 100; ++k) {
				Ray ray = camera.getRay(j + Math::random(), i + Math::random());
				film.pixels[i][j] += color(ray, scene);
			}
			film.pixels[i][j] *= 0.01f;
		}
	}

	printf("\n");

	film.gammaCorrection();
	film.writePPM();

	return 0;
}
