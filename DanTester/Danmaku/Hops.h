#ifndef __HOPS_H__
#define __HOPS_H__

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
	Vector Rotate(float _rot);

	float X, Y;
};

typedef struct {
	float X, Y;
}Point2D;

#endif