#ifndef GUI_CAMERA_H
#define GUI_CAMERA_H

#include "vector3.h"

namespace gui {
	class Ray;
	class Film;

	class Camera {
	public:
		Camera(const Film& film, float fovy = 90, float apetrure = 0, float focal = 1);

		void lookAt(const Vector3& target);
		Ray getRay(float px, float py) const;

	public:
		const Film& film;
		float resolution;
		float apeture;
		float focal;

		Vector3 position;
		Vector3 x;
		Vector3 y;
		Vector3 z;
	};
}

#endif
