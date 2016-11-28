#ifndef GUI_AABB_H
#define GUI_AABB_H

#include "vector3.h"

namespace gui {
	class Ray;

	class AABB {
	public:
		AABB() { }

		AABB(const Vector3 min, const Vector3 max)
			: min(min), max(max)
		{ }

		bool intersect(const Ray& ray, float tMin, float tMax) const;

	public:
		Vector3 min;
		Vector3 max;
	};
}

#endif