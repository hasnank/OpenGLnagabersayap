#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/GL.h>

class Layer {
public:
	Layer(int layer) {
		this->layer = layer;
	}
	
	inline int* GetLayer() { return &layer; }
private:
	int layer;
};

class Vertex : public Layer{
public:
	Vertex(const glm::vec3& pos, const glm::vec3& color, const int& layer) : Layer(layer){
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
	Circle(const glm::vec3& pos, const glm::vec3& color, const float& radius, const int& layer) : Vertex(pos, color, layer) {
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
	static const unsigned int NUM_SEGMENTS = 50;
	static const unsigned int NUM_LAYERS = 3;
	GLuint m_vertexArrayObject[NUM_LAYERS][NUM_MODELS];
	GLuint m_vertexArrayBuffer[NUM_LAYERS][NUM_MODELS][NUM_BUFFERS];
	unsigned int m_drawCount[NUM_LAYERS][NUM_MODELS];
};

