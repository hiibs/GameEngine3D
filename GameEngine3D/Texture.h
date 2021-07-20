#pragma once
#include <glad/glad.h>

class Texture {
public:
	Texture(const char* filePath);
	~Texture();

	unsigned int id;
	const char* filePath;

	void load();
};

