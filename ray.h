#ifndef GUI_RAY_H
#define GUI_RAY_H

#include "vector3.h"

namespace gui {
	class Ray {
	public:
		Ray() { }

		Ray(const Vector3& origin, const Vector3& direction)
			: origin(origin), direction(direction)
		{ }

	public:
		Vector3 origin;
		Vector3 direction;
	};
}

#endif
