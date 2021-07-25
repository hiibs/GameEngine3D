#include "CubeMap.h"
#include <glad/glad.h>

CubeMap::CubeMap() {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}
