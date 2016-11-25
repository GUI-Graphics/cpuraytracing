#include "scene.h"
#include "intersection.h"

namespace gui {
	bool Scene::intersect(
		const Ray& ray,
		float tMin,
		float tMax,
		Intersection& intersection) const {
			
		bool intersected = false;
		for(auto e : shapes) {
			if(e->intersect(ray, tMin, tMax, intersection)) {
				if(intersection.t < tMax) {
					tMax = intersection.t;
					intersected = true;
				}
			}
		}
		return intersected;
	}
}
