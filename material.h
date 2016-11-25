#ifndef GUI_MATERIAL_H
#define GUI_MATERIAL_H

namespace gui {
	class Ray;
	class Vector3;
	class Intersection;

	class Material {
	public:
		virtual ~Material()
		{ }

		virtual bool scatter(
			const Ray& in,
			const Intersection& intersection,
			Vector3& attenuation,
			Ray& scattered
		) const = 0;
	};
}

#endif
