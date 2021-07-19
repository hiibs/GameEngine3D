#include "Mesh.h"

Mesh::Mesh(std::string name, Vector3 position, Quaternion rotation, Vector3 scale, Object* parent, std::string sourceFile, Material* material) :
	Object(name, position, rotation, scale, parent),
	sourceFile(sourceFile),
	material(material)
{
}
