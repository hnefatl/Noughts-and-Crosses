#ifndef _VECTOR_H
#define _VECTOR_H

class Vector
{
public:
	Vector();
	Vector(unsigned int X, unsigned int Y);

	bool operator ==(const Vector &One) const;

	unsigned int X, Y;
};

#endif