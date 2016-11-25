#include "ray.h"
#include "film.h"
#include "camera.h"

#include <stdio.h>

namespace gui {
	Ray Camera::getRay(float px, float py) const {
		float u = (px - film.width * 0.5f) / resolution;
		float v = (film.height * 0.5f - py) / resolution;
		return Ray(Vector3(0), Vector3(u, v, -1));
	}
}
