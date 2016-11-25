#ifndef GUI_SHAPE_H
#define GUI_SHAPE_H

#include "material.h"

namespace gui {
	class Ray;
	class Intersection;

	class Shape {
	public:
		Shape(Material* material = nullptr): material(material)
		{ }

		virtual ~Shape() {
			delete material;
		}

		virtual bool intersect(
			const Ray& ray,
			float tMin,
			float tMax,
			Intersection& intersection
		) const = 0;

	public:
		Material* material;
	};
}

#endif
