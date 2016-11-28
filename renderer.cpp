#include "ray.h"
#include "math.h"
#include "film.h"
#include "scene.h"
#include "camera.h"
#include "renderer.h"
#include "intersection.h"

namespace gui {
	long long Renderer::nIntersects = 0;

	Vector3 Renderer::radiance(const Ray& ray, const Scene& scene, int depth) const {
		Intersection intersection;
		if (scene.intersect(ray, 0, 10000, intersection)) {
			Ray scattered;
			Vector3 attenuation;
			if (intersection.material->scatter(
				ray, intersection, attenuation, scattered) && depth < 30) {
				return attenuation * radiance(scattered, scene, ++depth);
			} else {
				return Vector3(0);
			}
		} else {
			Vector3 unit = ray.direction;
			float k = (unit.identity().y + 1) * 0.5f;
			return Vector3(1) * (1 - k) + Vector3(0.5f, 0.7f, 1) * k;
		}
	}

	void Renderer::render(const Scene& scene, Camera& camera) const {
		float r = 1.0f / samples;
		for(int i = 0; i < camera.film.height; ++i) {
			printf("\rrendering %5.2f%%", 100.0f * (i + 1) / camera.film.height);
			fflush(stdout);
			for(int j = 0; j < camera.film.width; ++j) {
				for (int k = 0; k < samples; ++k) {
					Ray ray = camera.getRay(j + Math::random(), i + Math::random());
					camera.film.pixels[i][j] += radiance(ray, scene, 0);
				}
				camera.film.pixels[i][j] *= r;
			}
		}

		printf("\nstatistical data:\n");
		printf("num intersects: %lld\n", nIntersects);

		camera.film.gammaCorrection();
		camera.film.writePPM();
	}
}
