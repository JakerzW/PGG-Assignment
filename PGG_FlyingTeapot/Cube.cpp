#include "Cube.h"
#include "Stars.h"

Cube::Cube()
{
	// Create and bind VAO
	_VAO = 0;
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Vertex data for the quad
	float vertices[] =
	{
		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,


		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,

		0.5f,-0.5f, 0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,


		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f, 0.5f,

		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,


		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,

		-0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,


		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,

		0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f
	};
	// Set the number of vertices for the quad
	_numVertices = 30;

	// Variable to store a VBO
	GLuint buffer = 0;
	// Create and bind a generic buffer
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	float normals[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		0.0f, 0.0f,-1.0f,
		0.0f, 0.0f,-1.0f,
		0.0f, 0.0f,-1.0f,

		0.0f, 0.0f,-1.0f,
		0.0f, 0.0f,-1.0f,
		0.0f, 0.0f,-1.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &_VAO);
}

void Cube::Draw()
{
	glBindVertexArray(_VAO);

	glDrawArrays(GL_TRIANGLES, 0, _numVertices);

	glBindVertexArray(0);
}

glm::mat4 Stars::GetModelMatrix()
{
	return glm::mat4();
}
