#ifndef Vector_H_INCLUDED
#define Vector_H_INCLUDED

#include <iostream>

class Vector {
private: float v[3];
public: Vector();
		Vector(float x, float y, float z);

		float &operator[] (int index);
		float operator[] (int index) const;

		Vector operator* (float scale) const;
		Vector operator/ (float scale) const;
		Vector operator+ (const Vector &other) const;
		Vector operator- (const Vector &other) const;

		const Vector &operator*= (float scale);
		const Vector &operator/= (float scale);
		const Vector &operator+= (const Vector &other);
		const Vector &operator-= (const Vector &other);

		float magnitude() const;
		float magnitudeSquare() const;
		Vector normalize() const;
		float dot(const Vector &other) const;
		Vector cross(const Vector &other) const;
};

Vector operator*(float scale, const Vector &v);
std::ostream &operator<<(std::ostream &output, const Vector &v);



#endif