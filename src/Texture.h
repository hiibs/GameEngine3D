#pragma once
#include <string>

class Texture {
public:
	Texture(std::string fileName);
	~Texture();

	unsigned int id;
	std::string filePath;

	void load();
};

