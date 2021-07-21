#version 330 core

struct PointLight {
	vec3 position;
	vec3 color;
	float intensity;
	float radius;
};

struct DirLight {
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform PointLight pointLights[5];
uniform DirLight dirLights[5];
uniform int numPointLights;
uniform int numDirLights;
uniform vec3 ambientColor;
uniform float ambientIntensity;
uniform sampler2D colorMap;


in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

void main() {
	vec3 lightResult = vec3(0.0);
	
	// Directional lights
	for (int i = 0; i < numDirLights; i++){
		vec3 diff = max(dot(normal, -dirLights[i].direction), 0.0) * dirLights[i].color * dirLights[i].intensity;
		lightResult += diff;
	}

	// Point lights
	for (int i = 0; i < numPointLights; i++) {
		vec3 lightDir = normalize(pointLights[i].position - fragPos);
		float distance = length(pointLights[i].position - fragPos);
		float attenuation = pow(clamp(1.0 - distance / pointLights[i].radius, 0.0, 1.0), 2);

		vec3 diff = max(dot(normal, lightDir), 0.0) * pointLights[i].color * pointLights[i].intensity * attenuation;

		lightResult += diff;
	}

	

	lightResult += ambientColor * ambientIntensity;


	FragColor = vec4(lightResult * vec3(texture(colorMap, texCoord)), 0.0);
}