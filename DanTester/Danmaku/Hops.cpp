#include "Hops.h"
#include <math.h>


Vector::Vector(float _x, float _y) {
	X = _x;
	Y = _y;
}

Vector::Vector(const Vector & _v) {
	X = _v.X;
	Y = _v.Y;
}

Vector Vector::operator+(Vector & _o) {
	return Vector(X + _o.X, Y + _o.Y);
}

Vector Vector::operator-(Vector & _o) {
	return Vector(X - _o.X, Y - _o.Y);
}

Vector Vector::operator=(Vector & _o) {
	X = _o.X; Y = _o.Y;
	return Vector(X, Y);
}

Vector Vector::operator+=(Vector & _o) {
	X = X + _o.X;
	Y = Y + _o.Y;
	return Vector(X, Y);
}

Vector Vector::operator-=(Vector & _o) {
	X = X - _o.X;
	Y = Y - _o.Y;
	return Vector(X, Y);
}

bool Vector::operator==(Vector & _o) {
	return (X == _o.X && Y == _o.Y);
}

bool Vector::operator!=(Vector & _o) {
	return (X != _o.X || Y != _o.Y);
}

Vector Vector::Rotate(float _ang) {
	float _rot = _ang * PI / 180;
	return Vector(X * cos(_rot) - Y * sin(_rot), X * sin(_rot) + Y*cos(_rot));
}
