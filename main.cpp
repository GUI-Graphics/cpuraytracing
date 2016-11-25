#include <iostream>

#include "math.h"
#include "vector3.h"

using namespace gui;

int main() {
	for(int i = 0; i < 100; ++i) {
		Vector3 v = Math::randomDisk();
		std::cout << v.length() << std::endl;
	}
	return 0;
}
