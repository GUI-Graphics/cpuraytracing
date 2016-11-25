#include <fstream>

#include "film.h"
#include "vector3.h"

namespace gui {
	Film::Film(int width, int height) : width(width), height(height) {
		pixels = new Vector3*[height];
		for(int i = 0; i < height; ++i) {
			pixels[i] = new Vector3[width];
			for (int j = 0; j < width; ++j) {
				pixels[i][j] = Vector3(0);
			}
		}
	}

	Film::~Film() {
		for(int i = 0; i < height; ++i) {
			delete[] pixels[i];
		}
		delete[] pixels;
	}

	void Film::gammaCorrection() {
		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < width; ++j) {
				Vector3& c = pixels[i][j];
				c.x = sqrtf(c.x);
				c.y = sqrtf(c.y);
				c.z = sqrtf(c.z);
			}
		}
	}

	void Film::writePPM() const {
		std::ofstream file;
		file.open("image.ppm");
		file << "P3\n" << width << ' ' << height << '\n' << "255\n";
		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < width; ++j) {
				file << (int) (pixels[i][j].x * 255) << ' '
					 << (int) (pixels[i][j].y * 255) << ' '
					 << (int) (pixels[i][j].z * 255) << ' ';
			}
			file << '\n';
		}
		file.close();
	}
}
