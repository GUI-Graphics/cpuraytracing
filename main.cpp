#include <iostream>

#include "math.h"
#include "vector3.h"

#include "ray.h"
#include "film.h"
#include "camera.h"

#include "scene.h"
#include "sphere.h"
#include "intersection.h"

#include "metal.h"
#include "diffuse.h"
#include "dielectric.h"

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
	for(int i = -11; i < 11; ++i) {
		for(int j = -11; j < 11; ++j) {
			Vector3 c(i + 0.9f * Math::random(), 0.2f, j + 0.9f * Math::random());
			float p = Math::random();
			if(p < 0.8f) {
				shapes.push_back(new Sphere(c, 0.2f, new Diffuse(Vector3(Math::random(), Math::random(), Math::random()))));
			} else if(p < 0.95f) {
				float r = 0.5f * (1 + Math::random());
				float g = 0.5f * (1 + Math::random());
				float b = 0.5f * (1 + Math::random());
				shapes.push_back(new Sphere(c, 0.2f, new Metal(Vector3(r, g, b), 0.5f * Math::random())));
			} else {
				shapes.push_back(new Sphere(c, 0.2f, new Dielectric(1.5f)));
			}
		}
	}
	shapes.push_back(new Sphere(Vector3(0, 1, 0), 1, new Dielectric(1.5f)));
	shapes.push_back(new Sphere(Vector3(-4, 1, 0), 1, new Diffuse(Vector3(0.4f, 0.2f, 0.1f))));
	shapes.push_back(new Sphere(Vector3(4, 1, 0), 1, new Metal(Vector3(0.7f, 0.6f, 0.5f))));
	shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000, new Diffuse(Vector3(0.5f))));
}

int main() {
	Film film;
	Camera camera(film, 20, 0.1f, 12);
	camera.position = Vector3(12, 2, 3);
	camera.lookAt(Vector3(0, 1, 0));

	Scene scene;
	initScene(scene);

	for(int i = 0; i < film.height; ++i) {
		printf("\rrendering %5.2f%%", 100.0f * (i + 1) / film.height);
		fflush(stdout);
		for(int j = 0; j < film.width; ++j) {
			for (int k = 0; k < 1000; ++k) {
				Ray ray = camera.getRay(j + Math::random(), i + Math::random());
				film.pixels[i][j] += color(ray, scene, 0);
			}
			film.pixels[i][j] *= 0.001f;
		}
	}

	printf("\n");

	film.gammaCorrection();
	film.writePPM();

	return 0;
}
