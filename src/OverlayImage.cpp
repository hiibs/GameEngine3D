#include "OverlayImage.h"
#include <glad/glad.h>
#include <glm/gtx/transform.hpp>

OverlayImage::OverlayImage(Camera* camera) :
	anchorPoint(glm::vec2(0.f)),
	size(glm::vec2(128.f)),
	offset(glm::vec2(0.f)),
	camera(camera)
{
	camera->addOverlay(this);

	// Quad vertices
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, // bottom left  
		1.0f, -1.0f, 0.0f, // bottom right 
		-1.0f, 1.0f, 0.0f, // top left
		-1.0f, 1.0f, 0.0f, // top left
		1.0f, -1.0f, 0.0f, // bottom right
		1.0f, 1.0f, 0.0f // top right
	};

	// Texture coordinates
	float texCoords[] = {
		0.0f, 1.0f,    // left-bottom
		1.0f, 1.0f,    // right-bottom
		0.0f, 0.0f,    // top-left
		0.0f, 0.0f,    // top-left
		1.0f, 1.0f,    // right-bottom
		1.0f, 0.0f,    // top-right
	};

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);

	// Create Vertex Buffer Object
	glGenBuffers(1, &positionsVbo);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
	// configure vertex attributes(s).
	glBindVertexArray(vao);

	// Set buffer data to m_vbo-object (bind buffer first and then set the data)
	glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex 
	// attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	// Create texture coordinate VBO
	glGenBuffers(1, &texCoordsVbo);

	// Set buffer data to m_texCoordsVbo-object (bind buffer first and then set the data)
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this
	// VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray
	// anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

OverlayImage::~OverlayImage() {
	camera->removeOverlay(this);
}

const glm::mat4 OverlayImage::getModelMatrix() const {
	return glm::translate(glm::mat4(1.f), glm::vec3(offset, 1.f)) * 
		glm::scale(glm::mat4(1.f), glm::vec3(size, 1.f));
}

unsigned int OverlayImage::getVao() const {
	return vao;
}
