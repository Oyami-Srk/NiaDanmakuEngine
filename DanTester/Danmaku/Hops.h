#ifndef __HOPS_H__
#define __HOPS_H__

#define PI (acos(-1.0))

class Vector {
public:
	Vector(float _x, float _y);
	Vector(const Vector& _v);
	Vector operator+(Vector& _o);
	Vector operator-(Vector& _o);
	Vector operator=(Vector& _o);
	Vector operator+=(Vector& _o);
	Vector operator-=(Vector& _o);
	bool operator==(Vector& _o);
	bool operator!=(Vector& _o);
	Vector Rotate(float _ang);

	float X, Y;
};

typedef struct {
	float X, Y;
}Point2D;

#endif