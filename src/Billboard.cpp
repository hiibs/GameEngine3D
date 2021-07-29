#include "Billboard.h"
#include "Engine.h"
#include <glad/glad.h>

Billboard::Billboard(Scene* scene) : Object(scene) {
	// Quad vertices
	float vertices[] = {
		-0.5f, 0.0f, -0.5f, // bottom left  
		-0.5f, 0.0f, 0.5f, // top left
		0.5f, 0.0f, -0.5f, // bottom right 
		-0.5f, 0.0f, 0.5f, // top left
		0.5f, 0.0f, 0.5f, // top right
		0.5f, 0.0f, -0.5f // bottom right
	};

	// Texture coordinates
	float texCoords[] = {
		0.0f, 1.0f,    // left-bottom
		0.0f, 0.0f,    // top-left
		1.0f, 1.0f,    // right-bottom
		0.0f, 0.0f,    // top-left
		1.0f, 0.0f,    // top-right
		1.0f, 1.0f    // right-bottom
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

	Engine::getInstance()->getRenderer()->addBillboard(this);
}

Billboard::~Billboard() {
	Engine::getInstance()->getRenderer()->removeBillboard(this);
}

glm::mat4 Billboard::getBillboardMatrix(glm::vec3 viewPos, glm::vec3 up) const {
	glm::vec3 look = -glm::normalize(viewPos - getWorldPosition());
	glm::vec3 right = glm::normalize(glm::cross(up, look));
	glm::vec3 up2 = glm::normalize(cross(look, right));
	glm::mat4 transform;
	transform[0] = glm::vec4(getScale().x * right, 0.f);
	transform[1] = glm::vec4(getScale().y * look, 0.f);
	transform[2] = glm::vec4(getScale().z * up2, 0.f);
	transform[3] = glm::vec4(getWorldPosition(), 1.f);
	return transform;
}

unsigned int Billboard::getVao() const {
	return vao;
}
