#include <iostream>

#include "Vector3D.h"

Vector3D::Vector3D(const Vector3D& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

int Vector3D::get_x() {
	return x;
}

int Vector3D::get_y() {
	return y;
}

int Vector3D::get_z() {
	return z;
}

std::string Vector3D::get_coord() {
	std::string coord = "";
	coord += std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
	return coord;
}

float Vector3D::module() {
	return pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5);
}

Vector3D Vector3D::operator+(const Vector3D& vec) {
	return Vector3D(x + vec.x, y + vec.y, z + vec.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& vec) {
	return Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3D Vector3D::operator*(int value) {
	return Vector3D(x * value, y * value, z * value);
}

Vector3D& Vector3D::operator*=(int value) {
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3D Vector3D::operator*(const Vector3D& vec) {
	return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

void Vector3D::disp() {
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}