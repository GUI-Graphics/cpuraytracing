#ifndef GUI_SCENE_H
#define GUI_SCENE_H

#include <vector>

#include "shape.h"
#include "intersection.h"

namespace gui {
	class Scene : public Shape {
	public:
		Scene()
		{ }

		~Scene() {
			for(auto e : shapes) {
				delete e;
			}
		}

		bool intersect(
			const Ray& ray,
			float tMin,
			float tMax,
			Intersection& intersection
		) const override;

	public:
		std::vector<Shape*> shapes;
	};
}

#endif
