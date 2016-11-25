#ifndef GUI_SHAPE_H
#define GUI_SHAPE_H

namespace gui {
	class Ray;
	class Intersection;

	class Shape {
	public:
		virtual ~Shape()
		{ }
		
		virtual bool intersect(
			const Ray& ray,
			float tMin,
			float tMax,
			Intersection& intersection
		) const = 0;
	};
}

#endif
