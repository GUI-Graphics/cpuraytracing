#include "ray.h"
#include "film.h"
#include "math.h"
#include "camera.h"

namespace gui {
	Camera::Camera(Film& film, float fovy, float apeture, float focal)
		: film(film)
		, apeture(apeture)
		, focal(focal)
		, position(Vector3(0))
		, x(Vector3(1, 0, 0))
		, y(Vector3(0, 1, 0))
		, z(Vector3(0, 0, 1)) {

		float radian = fovy / 180 * Math::PI;
		resolution = film.height * 0.5f / tanf(0.5f * radian);
	}

	Ray Camera::getRay(float px, float py) const {
		Vector3 offset = Math::randomDisk() * apeture;
		offset = x * offset.x + y * offset.y;
		float u = (px - film.width * 0.5f) / resolution;
		float v = (film.height * 0.5f - py) / resolution;
		return Ray(position + offset, x * u + y * v - z - offset / focal);
	}

	void Camera::lookAt(const Vector3& target) {
		z = (position - target).identity();
		x = Vector3(0, 1, 0).cross(z).identity();
		y = z.cross(x);
	}
}
