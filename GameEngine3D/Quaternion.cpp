#include "Quaternion.h"

Quaternion::Quaternion() :
	w(1.f),
	x(0.f),
	y(0.f),
	z(0.f)
{
}

Quaternion::Quaternion(float w, float x, float y, float z) :
	w(w),
	x(x),
	y(y),
	z(z)
{
}
