#include <iostream>

#include "ray.h"
#include "math.h"
#include "film.h"
#include "scene.h"
#include "sphere.h"
#include "camera.h"
#include "vector3.h"
#include "diffuse.h"

using namespace gui;

Vector3 color(const Ray& ray, const Scene& scene, int depth) {
	Intersection intersection;
	if(scene.intersect(ray, 0, 10000, intersection)) {
		Ray scattered;
		Vector3 attenuation;
		if(intersection.material->scatter(
			ray, intersection, attenuation, scattered) && depth < 30) {
			return color(scattered, scene, ++depth);
		} else {
			return Vector3(0);
		}
	} else {
		float k = (ray.direction.y + 1) * 0.5f;
		return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
	}
}

void initScene(Scene& scene) {
	auto& shapes = scene.shapes;
	// shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000));
	// for(int i = -2; i < 2; ++i) {
	// 	for(int j = -2; j < 2; ++j) {
	// 		Vector3 c(i + 0.9f * Math::random(), 0.2f, j + 0.9f * Math::random());
	// 		float p = Math::random();
	// 		if(p < 0.8f) {
	// 			shapes.push_back(new Sphere(c, 0.2));
	// 		} else if(p < 0.95f) {
	// 			shapes.push_back(new Sphere(c, 0.2));
	// 		} else {
	// 			shapes.push_back(new Sphere(c, 0.2));
	// 		}
	// 	}
	// }
	// shapes.push_back(new Sphere(Vector3(0, 1, 0), 1));
	// shapes.push_back(new Sphere(Vector3(-4, 1, 0), 1));
	// shapes.push_back(new Sphere(Vector3(4, 1, 0), 1));

	shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000, new Diffuse(Vector3(1))));
	shapes.push_back(new Sphere(Vector3(0, 0.2f, -1), 0.2f, new Diffuse(Vector3(1))));
}

int main() {
	Film film(512, 256);
	Camera camera(film);
	camera.position = Vector3(13, 2, 3);
	camera.lookAt(Vector3(0));

	Scene scene;
	initScene(scene);

	for(int i = 0; i < film.height; ++i) {
		printf("\rrendering %5.2f%%", 100.0f * (i + 1) / film.height);
		for(int j = 0; j < film.width; ++j) {
			for(int k = 0; k < 10; ++k) {
				Ray ray = camera.getRay(j + Math::random(), i + Math::random());
				film.pixels[i][j] += color(ray, scene, 0);
			}
			film.pixels[i][j] *= 0.1f;
		}
	}

	printf("\n");

	film.gammaCorrection();
	film.writePPM();

	return 0;
}
