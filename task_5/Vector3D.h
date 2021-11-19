#pragma once
#include <string>
#include <cmath> //pow

class Vector3D {
private:
	int x, y, z;

public:
	//empty constructor
	Vector3D() {
		x = y = z = 0;
	}

	//constructor from values
	Vector3D(int new_x, int new_y, int new_z) {
		x = new_x;
		y = new_y;
		z = new_z;
	}

	Vector3D(const Vector3D& vec); //copy constructor
	int get_x(); //return x
	int get_y(); //return y
	int get_z(); //return z
	std::string get_coord(); //return string of coordinates x y z

	float module(); //return vector module

	Vector3D operator+(const Vector3D& vec);    //addition
	Vector3D& operator+=(const Vector3D& vec);  //assigning result of addition to the vector
	Vector3D operator-(const Vector3D& vec);    //substraction
	Vector3D& operator-=(const Vector3D& vec);  //assigning result of substractuin to the vector

	Vector3D operator*(int value);    //scalar multiplication
	Vector3D& operator*=(int value);  //assigning result of vector multiplication to the vector

	Vector3D operator*(const Vector3D& vec); //cross product 

	void disp(); //print vector on screen
};