#include <algorithm>

#include "ray.h"
#include "aabb.h"

namespace gui {
	bool AABB::intersect(const Ray& ray, float tMin, float tMax) const {
		Vector3 d = ray.direction;
		Vector3 t0 = (min - ray.origin) / ray.direction;
		Vector3 t1 = (max - ray.origin) / ray.direction;
		if (t0.x > t1.x) std::swap(t0.x, t1.x);
		if(t0.y > t1.y) std::swap(t0)
		Vector3 ta = Vector3::min(t0, t1);
		Vector3 tb = Vector3::max(t0, t1);
	}
}