#pragma once
class Vector3 {
public:
	Vector3();
	Vector3(float x, float y, float z);
	
	// Default vectors
	static Vector3 zero() { return Vector3(0.f, 0.f, 0.f); };
	static Vector3 one() { return Vector3(1.f, 1.f, 1.f); };
	static Vector3 forward() { return Vector3(1.f, 0.f, 0.f); };
	static Vector3 right() { return Vector3(0.f, 1.f, 0.f); };
	static Vector3 up() { return Vector3(0.f, 0.f, 1.f); };

	float x, y, z;
};

