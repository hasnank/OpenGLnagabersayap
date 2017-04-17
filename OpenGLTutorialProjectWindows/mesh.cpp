#include "mesh.h"
#include <cstdio>
#include <cmath>
#include <vector>

void DrawCircle(float cx, float cy, float r, int num_segments);

Mesh::Mesh(Vertex* triangle, unsigned int numTriangles,
	GLuint* idxTri, unsigned int numIdxTri,
	Vertex* quad, unsigned int numQuads,
	GLuint* idxQuad, unsigned int numIdxQuad,
	Circle* circle, unsigned int numCircles)
{
	m_drawCount[TRIANGLE_IDX] = numIdxTri; // use Elements
	m_drawCount[QUAD_IDX] = numIdxQuad; // use Elements
	m_drawCount[CIRCLE_IDX] = numCircles; // use Array!

	glewExperimental = GL_TRUE;
	glewInit();

	glGenVertexArrays(NUM_MODELS, m_vertexArrayObject);

	std::vector<glm::vec3> positions[NUM_MODELS];
	std::vector<glm::vec3> colors[NUM_MODELS];
	std::vector<GLuint> indices[NUM_MODELS];
	std::vector<float> radiuses;

	std::vector<unsigned int> numVertices;
	std::vector<unsigned int> numIndices;
	// initialization Number of models done!
	
	// Initialization of m_vertexArrayObject
	for (unsigned int i = 0; i < NUM_MODELS; ++i) {
		glBindVertexArray(m_vertexArrayObject[i]); // bind

		switch (i) {
			case TRIANGLE_IDX:
				positions[i].reserve(numTriangles);
				colors[i].reserve(numTriangles);
				indices[i].reserve(numIdxTri);

				for (unsigned int j = 0; j < numTriangles; ++j) {
					positions[i].push_back(*triangle[j].GetPos());
					colors[i].push_back(*triangle[j].GetColor());
				}
				
				for (unsigned int j = 0; j < numIdxTri; ++j) {
					indices[i].push_back(idxTri[j]);
				}

				numVertices.push_back(numTriangles);
				numIndices.push_back(numIdxTri);

				break;

			case QUAD_IDX:
				positions[i].reserve(numQuads);
				colors[i].reserve(numQuads);
				indices[i].reserve(numIdxQuad);

				for (unsigned int j = 0; j < numQuads; ++j) {
					positions[i].push_back(*quad[j].GetPos());
					colors[i].push_back(*quad[j].GetColor());
				}

				for (unsigned int j = 0; j < numIdxQuad; ++j) {
					indices[i].push_back(idxQuad[j]);
				}

				numVertices.push_back(numQuads);
				numIndices.push_back(numIdxQuad);
				break;

			case CIRCLE_IDX:
				positions[i].reserve(numCircles);
				colors[i].reserve(numCircles);
				radiuses.reserve(numCircles);

				for (unsigned int j = 0; j < numCircles; ++j) {
					positions[i].push_back(*circle[j].GetPos());
					colors[i].push_back(*circle[j].GetColor());
					radiuses.push_back(*circle[j].GetRadius());
				}
				numVertices.push_back(numCircles);

				break;

			default:
				break;
		}
			
		glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer[i]); // in circle, indices is replaced by radiuses
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[i][POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, numVertices[i] * sizeof(positions[i][0]), &positions[i][0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[i][COLOR_VB]);
		glBufferData(GL_ARRAY_BUFFER, numVertices[i] * sizeof(colors[i][0]), &colors[i][0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (i != CIRCLE_IDX) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[i][INDEX_VB]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices[i] * sizeof(indices[i][0]), &indices[i][0], GL_STATIC_DRAW);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[i][INDEX_VB]); // should be RADIUS_VB
			glBufferData(GL_ARRAY_BUFFER, numVertices[i] * sizeof(radiuses[0]), &radiuses[0], GL_STATIC_DRAW);
		}
	}

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(NUM_MODELS, m_vertexArrayObject);
}

void Mesh::Draw() {
	for (unsigned int i = 0; i < NUM_MODELS; ++i) {
		glBindVertexArray(m_vertexArrayObject[i]); // bind

		switch (i) {
			case TRIANGLE_IDX:
				glDrawElements(GL_TRIANGLES, m_drawCount[i], GL_UNSIGNED_INT, 0);
				break;

			case QUAD_IDX:
				glDrawElements(GL_QUADS, m_drawCount[i], GL_UNSIGNED_INT, 0);
				break;

			case CIRCLE_IDX:
				break;
			default:
				break;
		}
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount);
		
		//printf("%d\n", m_drawCount);
		//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
		
	}
	glBindVertexArray(0); // unbind

	//SECTION Septi

	//SECTION Hishshah
	
	//SECTION Radit
	
	//SECTION Hasna
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