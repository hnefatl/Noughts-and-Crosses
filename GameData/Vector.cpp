#include "Vector.h"

Vector::Vector()
	:X(0),
	Y(0)
{

}
Vector::Vector(unsigned int X, unsigned int Y)
	:X(X),
	Y(Y)
{

}

bool Vector::operator ==(const Vector &One) const
{
	return (this->X==One.X) && (this->Y==One.Y);
}