#version 330 core

struct PointLight {
	vec3 position;
	vec3 color;
	float intensity;
	float radius;
};

uniform vec3 viewPos;
uniform vec3 ambientColor;
uniform float ambientIntensity;
uniform sampler2D colorMap;
uniform PointLight pointLights[10];
uniform int numPointLights;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

vec3 calcPointLight(PointLight light);

void main() {
	vec3 lightResult = vec3(0.0);

	pointLights[0].position = 0;
	
	for (int i = 0; i < numPointLights; i++) {
		lightResult += calcPointLight(pointLights[i]);
	}

	lightResult += ambientColor * ambientIntensity;


	FragColor = vec4(lightResult * vec3(texture(colorMap, texCoord)), 0.0);
}

vec3 calcPointLight(PointLight light) {
	vec3 lightDir = normalize(light.position - fragPos);
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 - clamp(light.radius / distance, 0.0, 1.1);

	vec3 diff = max(dot(normal, lightDir), 0.0) * light.color * attenuation;
	
	return vec3(0.0);
}