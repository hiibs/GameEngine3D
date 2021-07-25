#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Camera::Camera(Scene* scene) :
	Object(scene),
	fov(80.f),
	fpModelFov(40.f),
	nearClip(0.01f),
	farClip(1000.f)
{
	name = "Camera";
	projection = glm::mat4();
	fpModelProjection = glm::mat4();
}

void Camera::setAspect(int width, int height) {
	projection = glm::perspectiveFov(glm::radians(fov), (float)width, (float)height, nearClip, farClip) * glm::eulerAngleXYZ(-glm::half_pi<float>(), 0.f, 0.f);
	fpModelProjection = glm::perspectiveFov(glm::radians(fpModelFov), (float)width, (float)height, nearClip, farClip) * glm::eulerAngleXYZ(-glm::half_pi<float>(), 0.f, 0.f);
	uiProjection = glm::ortho(-width/2.f, width/2.f, -height/2.f, height/2.f);
}

void Camera::addOverlay(OverlayImage* overlay) {
	for (OverlayImage* o : overlays) {
		if (o == overlay)
			return;
	}

	overlays.push_back(overlay);
}

void Camera::removeOverlay(OverlayImage* overlay) {
	for (int i = 0; i < overlays.size(); i++) {
		if (overlay == overlays[i]) {
			delete overlay;
			overlays.erase(overlays.begin() + i);
		}
	}
}

const std::vector<OverlayImage*> Camera::getOverlays() const {
	return overlays;
}

const glm::mat4 Camera::getProjection() const {
	return projection;
}

const glm::mat4 Camera::getUiProjection() const {
	return uiProjection;
}

const glm::mat4 Camera::getFpModelProjection() const {
	return fpModelProjection;
}
