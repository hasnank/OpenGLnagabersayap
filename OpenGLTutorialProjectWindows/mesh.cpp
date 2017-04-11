#include "mesh.h"
#include <cstdio>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, GLuint* elements, unsigned int numIndices)
{
	//m_drawCount = numVertices;
	m_drawCount = numIndices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject); // bind

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(elements[0]), elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	
	glBindVertexArray(0); // unbind
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject); // bind

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount);
	//printf("%d\n", m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind
}