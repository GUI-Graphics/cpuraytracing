#ifndef GUI_CAMERA_H
#define GUI_CAMERA_H

#include <math.h>

#include "math.h"

namespace gui {
	class Ray;
	class Film;
	class Camera {
	public:
		Camera(const Film& film, float fovy = 90) : film(film) {
			float radian = fovy / 180 * Math::PI;
			resolution = film.height * 0.5f / tanf(0.5f * radian);
		}

		Ray getRay(float px, float py) const;

	public:
		const Film& film;
		float resolution;
	};
}

#endif
