#include "camera.h"
#include "renderer.h"

namespace gui {
	void Renderer::render(const Scene& scene, Camera& camera) {
		float r = 1.0f / samples;
		for(int i = 0; i < scene.film.height; ++i) {
			printf("\rrendering %5.2f%%", 100.0f * (i + 1) / scene.film.height);
			fflush(stdout);
			for(int j = 0; j < scene.film.width; ++j) {
				for (int k = 0; k < samples; ++k) {
					Ray ray = camera.getRay(j + Math::random(), i + Math::random());
					film.pixels[i][j] += color(ray, scene, 0);
				}
				film.pixels[i][j] *= r;
			}
		}

		printf("\n");

		film.gammaCorrection();
		film.writePPM();
	}
}
