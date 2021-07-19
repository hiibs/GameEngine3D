#include "Material.h"

Material::Material(std::string shaderFile, Texture* colorMap, Texture* normalMap, Texture* roughnessMap, Texture* metalnessMap) :
	shaderFile(shaderFile),
	colorMap(colorMap),
	normalMap(normalMap),
	roughnessMap(roughnessMap),
	metalnessMap(metalnessMap)
{
}
