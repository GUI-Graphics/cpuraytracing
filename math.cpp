#include "math.h"
#include "vector3.h"

namespace gui {
	const float Math::PI = 3.1415926f;

	std::random_device Math::device;
	std::mt19937 Math::generator(device());
	std::uniform_real_distribution<float> Math::distribution(0, 1);

	Vector3 Math::randomDisk() {
		Vector3 v;
		do {
			v = Vector3(Math::random(), Math::random(), 0) * 2 - Vector3(1, 1, 0);
		} while(v.length() > 1);
		return v;
	}

	Vector3 Math::randomSphere() {
		Vector3 v;
		do {
			v = Vector3(Math::random(), Math::random(), Math::random()) * 2 - Vector3(1);
		} while(v.length() > 1);
		return v;
	}
}
