#ifndef GUI_VECTOR3_H
#define GUI_VECTOR3_H

#include <cmath>
#include <stdlib.h>

namespace gui {
	class Vector3 {
	public:
		Vector3()
		{ }

		Vector3(float x) : x(x), y(x), z(x)
		{ }

		Vector3(float x, float y, float z) : x(x), y(y), z(z)
		{ }

		Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		Vector3 operator+(float k) const {
			return Vector3(x + k, y + k, z + k);
		}

		Vector3 operator-(float k) const {
			return Vector3(x - k, y - k, z - k);
		}

		Vector3 operator*(float k) const {
			return Vector3(x * k, y * k, z * k);
		}

		Vector3 operator/(float k) const {
			k = 1 / k;
			return Vector3(x * k, y * k, z * k);
		}

		Vector3& operator+=(float k) {
			x += k;
			y += k;
			z += k;
			return *this;
		}

		Vector3& operator-=(float k) {
			x -= k;
			y -= k;
			z -= k;
			return *this;
		}

		Vector3& operator*=(float k) {
			x *= k;
			y *= k;
			z *= k;
			return *this;
		}

		Vector3& operator/=(float k) {
			k = 1 / k;
			x *= k;
			y *= k;
			z *= k;
			return *this;
		}

		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator*(const Vector3& v) const {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		Vector3 operator/(const Vector3& v) const {
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		Vector3& operator+=(const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vector3& operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		Vector3& operator*=(const Vector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		Vector3& operator/=(const Vector3& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}

		bool operator==(const Vector3& v) const {
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vector3& v) const {
			return x != v.x || y != v.y || z != v.z;
		}

		Vector3& negate() {
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		Vector3& identity() {
			return *this *= (1 / length());
		}

		Vector3 cross(const Vector3& v) const {
			return Vector3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
			);
		}

		Vector3 reflect(const Vector3& normal) const {
			return *this - normal * this->dot(normal) * 2;
		}

		bool refract(const Vector3& normal, float niOverNt, Vector3& refracted) const {
			Vector3 v = Vector3(*this).identity();
			float c1 = v.dot(normal);
			float c2 = 1 - niOverNt * niOverNt * (1 - c1 * c1);
			if(c2 > 0) {
				refracted = (v - normal * c1) * niOverNt - normal * sqrt(c2);
				return true;
			}
			return false;
		}

		float dot(const Vector3& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		float length() const {
			return std::sqrt(lengthSquared());
		}

		float lengthSquared() const {
			return x * x + y * y + z * z;
		}
		
	public:
		float x, y, z;
	};
}

#endif
