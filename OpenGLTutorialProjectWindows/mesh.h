#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec3& color) {
		this->pos = pos;
		this->color = color;
	}

protected:
private:
	glm::vec3 pos;
	glm::vec3 color;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, GLuint* elements, unsigned int numIndices);
	virtual ~Mesh();

	void Draw();
protected:

private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& rhs){}

	enum {
		POSITION_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer[NUM_BUFFERS];
	unsigned int m_drawCount;
};

