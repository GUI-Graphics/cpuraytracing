#include "math.h"
#include "film.h"
#include "camera.h"
#include "renderer.h"

#include "scene.h"
#include "sphere.h"

#include "metal.h"
#include "diffuse.h"
#include "dielectric.h"

using namespace gui;

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
	Film film(256, 128);

	Camera camera(film, 20, 0.1f, 12);
	camera.position = Vector3(12, 2, 3);
	camera.lookAt(Vector3(0, 1, 0));

	Scene scene;
	initScene(scene);

	Renderer renderer(100);
	renderer.render(scene, camera);

	return 0;
}
