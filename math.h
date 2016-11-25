#ifndef GUI_MATH_H
#define GUI_MATH_H

#include <random>

namespace gui {
	class Vector3;
	
	class Math {
	public:
		static float random() {
			return distribution(generator);
		}

		static Vector3 randomDisk();
		static Vector3 randomSphere();

	public:
		static const float PI;

	private:
		static std::random_device device;
		static std::mt19937 generator;
		static std::uniform_real_distribution<float> distribution;
	};
}

#endif
