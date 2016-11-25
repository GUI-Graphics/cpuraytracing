#ifndef GUI_METAL_H
#define GUI_METAL_H

#include "vector3.h"
#include "material.h"

namespace gui {
	class Metal : public Material {
	public:
		Metal(const Vector3& albedo, float fuzzy = 0): albedo(albedo), fuzzy(fuzzy)
		{ }

		bool scatter(
			const Ray& in,
			const Intersection& intersection,
			Vector3& attenuation,
			Ray& scattered
		) const override;

	public:
		Vector3 albedo;
		float fuzzy;
	};
}

#endif