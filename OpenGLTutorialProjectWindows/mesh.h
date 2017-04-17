#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/GL.h>

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec3& color) {
		this->pos = pos;
		this->color = color;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetColor() { return &color; }

protected:
private:
	glm::vec3 pos;
	glm::vec3 color;
};

class Circle : public Vertex {
public:
	Circle(const glm::vec3& pos, const glm::vec3& color, const float& radius) : Vertex(pos, color) {
		this->radius = radius;
	}

	inline float* GetRadius() { return &radius; }
protected:

private:
	float radius;
};

class Mesh
{
public:
	Mesh(Vertex* triangles, unsigned int numTriangles, 
		GLuint* idxTri, unsigned int numIdxTri,
		Vertex* quad, unsigned int numQuad, 
		GLuint* idxQuad, unsigned int numIdxQuad,
		Circle* circle, unsigned int numCircles);
	virtual ~Mesh();

	void Draw();
protected:

private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& rhs) {}

	enum {
		POSITION_VB,
		COLOR_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	enum {
		TRIANGLE_IDX,
		QUAD_IDX,
		CIRCLE_IDX,
		NUM_MODELS
	};

	GLuint m_vertexArrayObject[NUM_MODELS];
	GLuint m_vertexArrayBuffer[NUM_MODELS][NUM_BUFFERS];
	unsigned int m_drawCount[NUM_MODELS];
};

