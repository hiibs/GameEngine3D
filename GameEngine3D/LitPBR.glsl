#version 330 core

uniform sampler2D texture0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientStrength;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

void main() {
	vec3 ambient = lightColor * ambientStrength;
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 norm = normalize(normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float specularStrength = 1;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 48);
	vec3 specular = specularStrength * spec * lightColor;
	vec4 result = vec4(ambient + diffuse, 1.f) * texture2D(texture0, texCoord) + vec4(specular.x, specular.y, specular.z, 1.f);
	FragColor = result;
}