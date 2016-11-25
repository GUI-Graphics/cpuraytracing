#include <cmath>

#include "ray.h"
#include "math.h"
#include "vector3.h"
#include "dielectric.h"
#include "intersection.h"

namespace gui {
	bool Dielectric::scatter(
		const Ray& in,
		const Intersection& intersection,
		Vector3& attenuation,
		Ray& scattered) const {

		attenuation = Vector3(1);

		float niOverNt;
		Vector3 normal;

		if (in.direction.dot(intersection.normal) > 0) {
			niOverNt = ior;
			normal = -intersection.normal;
		} else {
			niOverNt = 1 / ior;
			normal = intersection.normal;
		}

		float cosine = -in.direction.dot(normal) / in.direction.length();

		Vector3 refracted;
		Vector3 reflected = in.direction.reflect(normal);

		if (in.direction.refract(normal, niOverNt, refracted)) {
			if (Math::random() < schlick(cosine, niOverNt)) {
				scattered.direction = reflected;
			} else {
				scattered.direction = refracted;
			}
		} else {
			scattered.direction = reflected;
		}

		scattered.origin = intersection.position + scattered.direction * 0.0001f;

		return true;
	}

	float Dielectric::schlick(float cosine, float niOverNt) const {
		float r0 = (niOverNt - 1) / (niOverNt + 1);
		r0 *= r0;
		return r0 + (1 - r0) * pow(1 - cosine, 5);
	}
}