#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class OverlayImage;

class Camera : public Object {
public:
	Camera(Scene* scene);

	void setAspect(int width, int height);

	void addOverlay(OverlayImage* overlay);
	void removeOverlay(OverlayImage* overlay);

	const std::vector<OverlayImage*> getOverlays() const;

	const glm::mat4 getProjection() const;
	const glm::mat4 getFpModelProjection() const;
	const glm::mat4 getUiProjection() const;

private:
	glm::mat4 projection, fpModelProjection, uiProjection;
	float fov, nearClip, farClip, fpModelFov;

	std::vector<OverlayImage*> overlays;
};

