#include "mesh.h"
#include <cstdio>
#include <cmath>
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;
	
	glewExperimental = GL_TRUE;
	glewInit();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject); // bind

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; ++i) {
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void DrawCircle(float cx, float cy, float r, int num_segments);

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject); // bind

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount);
	
	

	//printf("%d\n", m_drawCount);
	//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind

	//SECTION Septi

	//SECTION Hishshah
	
	//SECTION Radit
	
	//SECTION Hasna

	// Example, belum bisa dengan warna
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 300; ++i) {
		float degInRad = i * 2 * acos(-1) / 300.0;
		float radius = 1;
		glVertex2f(cos(degInRad) * radius, sin(degInRad) * radius);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 150; ++i) {
		float degInRad = i * 2 * acos(-1) / 300.0;
		float radius = 0.5;
		glVertex2f(cos(degInRad) * radius, sin(degInRad) * radius);
	}
	glEnd();
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 
								   //calculate the tangential vector 
								   //remember, the radial vector is (x, y) 
								   //to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}