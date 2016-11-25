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
			return attenuation * color(scattered, scene, ++depth);
		} else {
			return Vector3(0);
		}
	} else {
		Vector3 unit = ray.direction;
		float k = (unit.identity().y + 1) * 0.5f;
		return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
	}
}

void initScene(Scene& scene) {
	auto& shapes = scene.shapes;
	//shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000, new Diffuse(Vector3(0.5))));
	for(int i = -11; i < 11; ++i) {
		for(int j = -11; j < 11; ++j) {
			Vector3 c(i + 0.9f * Math::random(), 0.2f, j + 0.9f * Math::random());
			float p = Math::random();
			if(p < 0.8f) {
				shapes.push_back(new Sphere(c, 0.2, new Diffuse(Vector3(0.5))));
			} else if(p < 0.95f) {
				shapes.push_back(new Sphere(c, 0.2, new Diffuse(Vector3(0.5))));
			} else {
				shapes.push_back(new Sphere(c, 0.2, new Diffuse(Vector3(0.5))));
			}
		}
	}
	shapes.push_back(new Sphere(Vector3(0, 1, 0), 1, new Diffuse(Vector3(0.5))));
	shapes.push_back(new Sphere(Vector3(-4, 1, 0), 1, new Diffuse(Vector3(0.5))));
	shapes.push_back(new Sphere(Vector3(4, 1, 0), 1, new Diffuse(Vector3(0.5))));
	shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000, new Diffuse(Vector3(0.5))));
}

int main() {
	Film film(512, 256);
	Camera camera(film, 20);
	// camera.position = Vector3(0, 0.5, 1);
	camera.position = Vector3(12, 2, 3);
	camera.lookAt(Vector3(0, 1, 0));

	Scene scene;
	initScene(scene);

	for(int i = 0; i < film.height; ++i) {
		printf("\rrendering %5.2f%%", 100.0f * (i + 1) / film.height);
		for(int j = 0; j < film.width; ++j) {
			for (int k = 0; k < 10; ++k) {
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
