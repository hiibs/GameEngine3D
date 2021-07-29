#pragma once
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"
#include "Billboard.h"
#include <vector>

class Renderer {
public:
	void draw();

	void addMesh(const Mesh* mesh);
	void removeMesh(const Mesh* mesh);

	void addBillboard(const Billboard* billboard);
	void removeBillboard(const Billboard* billboard);

	const Scene* scene;
	Camera* camera;
private:
	std::vector<const Mesh*> meshes;
	std::vector<const Billboard*> billboards;

	void drawMesh(const Mesh* mesh, glm::mat4 vp);
	void drawBillboard(const Billboard* billboard, glm::mat4 vp);
	void drawOverlay(OverlayImage* overlay);
};

