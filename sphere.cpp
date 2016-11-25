#include "ray.h"
#include "sphere.h"
#include "intersection.h"

namespace gui {
	bool Sphere::intersect(
		const Ray& ray,
		float tMin,
		float tMax,
		Intersection& intersection) const {

			Vector3 co = ray.origin - center;
			float a = ray.direction.lengthSquared();
			float b = ray.direction.dot(co);
			float c = co.lengthSquared() - radius * radius;
			float delta = b * b - a * c;

			if(delta < 0) return false;

			delta = sqrt(delta);
			float t = (-b - delta) / a;

			if(t > tMin && t < tMax) {
				intersection.t = t;
				intersection.position = ray.origin + ray.direction * t;
				intersection.normal = (intersection.position - center) / radius;
				intersection.material = material;
				return true;
			}

			t = (-b + delta) / a;
			if(t > tMin && t < tMax) {
				intersection.t = t;
				intersection.position = ray.origin + ray.direction * t;
				intersection.normal = (intersection.position - center) / radius;
				intersection.material = material;
				return true;
			}

			return false;
	}
}
