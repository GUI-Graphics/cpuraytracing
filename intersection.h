#ifndef GUI_INTERSECTION_H
#define GUI_INTERSECTION_H

#include <limits>

#include "vector3.h"

namespace gui {
	class Intersection {
	public:
		Intersection() : t(std::numeric_limits<float>::max())
		{ }

	public:
		float t;
		Vector3 position;
		Vector3 normal;
	};
}

#endif
