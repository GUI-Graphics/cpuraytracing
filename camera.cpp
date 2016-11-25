#include "ray.h"
#include "camera.h"

#include <stdio.h>

namespace gui {
	Camera::Camera(const Film& film, float fovy)
		: film(film)
		, position(Vector3(0))
		, x(Vector3(1, 0, 0))
		, y(Vector3(0, 1, 0))
		, z(Vector3(0, 0, 1)) {

		float radian = fovy / 180 * Math::PI;
		resolution = film.height * 0.5f / tanf(0.5f * radian);
	}

	Ray Camera::getRay(float px, float py) const {
		float u = (px - film.width * 0.5f) / resolution;
		float v = (film.height * 0.5f - py) / resolution;
		return Ray(Vector3(0), Vector3(u, v, -1));
	}

	void Camera::lookAt(const Vector3& target) {
		z = (position - target).identity();
		x = Vector3(0, 1, 0).cross(z).identity();
		y = z.cross(x);
	}
}
