#ifndef GUI_SPHERE_H
#define GUI_SPHERE_H

#include "shape.h"
#include "vector3.h"
#include "material.h"

namespace gui {
	class Ray;
	class Intersection;

	class Sphere : public Shape {
	public:
		Sphere(const Vector3& center, float radius, Material* material)
			: center(center), radius(radius) {

			this->material = material;
		}

		bool intersect(
			const Ray& ray,
			float tMin,
			float tMax,
			Intersection& intersection
		) const override;

	public:
		Vector3 center;
		float radius;
	};
}

#endif
