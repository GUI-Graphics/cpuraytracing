#include "ray.h"
#include "math.h"
#include "metal.h"
#include "intersection.h"

namespace gui {
	bool Metal::scatter(
		const Ray& in,
		const Intersection& intersection,
		Vector3& attenuation, Ray& scattered) const {

		attenuation = albedo;
		scattered.origin = intersection.position + intersection.normal * 0.001f;
		scattered.direction = in.direction.reflect(intersection.normal) + Math::randomSphere() * fuzzy;
		if (scattered.direction.dot(intersection.normal) > 0) return true;
		return false;
	}
}