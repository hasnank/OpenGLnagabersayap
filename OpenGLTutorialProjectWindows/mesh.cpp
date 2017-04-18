#include "mesh.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <map>

std::vector<glm::vec3> generateCircle(glm::vec3 center, float radius, unsigned int SEGMENTS);

Mesh::Mesh(Vertex* triangle, unsigned int numTriangles,
	GLuint* idxTri, unsigned int numIdxTri,
	Vertex* quad, unsigned int numQuads,
	GLuint* idxQuad, unsigned int numIdxQuad,
	Circle* circle, unsigned int numCircles) {

	glewExperimental = GL_TRUE;
	glewInit();

	/* START OF COUNT INITIALIZATION */
	for (unsigned int idx_layer = 0; idx_layer < NUM_LAYERS; ++idx_layer) {
		m_drawCount[idx_layer][TRIANGLE_IDX] = 0;
		m_drawCount[idx_layer][QUAD_IDX] = 0;
		m_drawCount[idx_layer][CIRCLE_IDX] = 0;
	}

	/* Indices Initialization */
	for (unsigned int i = 0; i < numIdxTri; ++i) // use Elements!
		m_drawCount[*triangle[idxTri[i]].GetLayer()][TRIANGLE_IDX]++;

	for (unsigned int i = 0; i < numIdxQuad; ++i) // use Elements!
		m_drawCount[*quad[idxQuad[i]].GetLayer()][QUAD_IDX]++;

	for (unsigned int i = 0; i < numCircles; ++i) // use Array!
		m_drawCount[*circle[i].GetLayer()][CIRCLE_IDX] ++;

	unsigned int m_vertexCount[NUM_LAYERS][NUM_MODELS];
	for (unsigned int i = 0; i < NUM_LAYERS; ++i)
		for (unsigned int j = 0; j < NUM_MODELS; ++j)
			m_vertexCount[i][j] = 0;

	/* Vertexes Initialization */
	for (unsigned int i = 0; i < numTriangles; ++i)
		m_vertexCount[*triangle[i].GetLayer()][TRIANGLE_IDX]++;

	for (unsigned int i = 0; i < numQuads; ++i)
		m_vertexCount[*quad[i].GetLayer()][QUAD_IDX]++;

	for (unsigned int i = 0; i < numCircles; ++i)
		m_vertexCount[*circle[i].GetLayer()][CIRCLE_IDX] += (NUM_SEGMENTS + 1);
	
	/* END OF COUNT INITIALIZATION */
	
	/* START OF DEBUG */

	/*
	printf("VERTEX COUNT:\n");
	for (unsigned int i = 0; i < NUM_LAYERS; ++i) {
		for (unsigned int j = 0; j < NUM_MODELS; ++j) {
			printf("%d,%d: %d\n", i, j, m_vertexCount[i][j]);
		}
		puts("");
	}
		
	printf("DRAW COUNT:\n");
	for (unsigned int i = 0; i < NUM_LAYERS; ++i) {
		for (unsigned int j = 0; j < NUM_MODELS; ++j) {
			printf("%d,%d: %d\n", i, j, m_drawCount[i][j]);
		}
		puts("");
	}
	*/

	/* END OF DEBUG */
	
	for (unsigned int idx_layer = 0; idx_layer < NUM_LAYERS; ++idx_layer) {
		glGenVertexArrays(NUM_MODELS, m_vertexArrayObject[idx_layer]);

		// Initialization of m_vertexArrayObject
		for (unsigned int i = 0; i < NUM_MODELS; ++i) {
			glBindVertexArray(m_vertexArrayObject[idx_layer][i]); // bind
			
			std::vector<glm::vec3> positions;
			std::vector<glm::vec3> colors;
			std::vector<GLuint> indices;

			if (i != CIRCLE_IDX) {
				positions.reserve(m_vertexCount[idx_layer][i]);
				colors.reserve(m_vertexCount[idx_layer][i]);
				indices.reserve(m_drawCount[idx_layer][i]);
			} 
			else {
				positions.reserve(m_vertexCount[idx_layer][i] );
				colors.reserve(m_vertexCount[idx_layer][i]);
			}

			std::map<unsigned int, unsigned int> globalToLocal; globalToLocal.clear();

			switch (i) {
				case TRIANGLE_IDX:

					for (unsigned int j = 0, idxNow = 0; j < numTriangles; ++j) {
						if (*triangle[j].GetLayer() == idx_layer) {
							globalToLocal[j] = idxNow;
							idxNow++;
							positions.push_back(*triangle[j].GetPos());
							colors.push_back(*triangle[j].GetColor()); 
						}
					}

					for (unsigned int j = 0; j < numIdxTri; ++j) {
						if (globalToLocal.count(idxTri[j])) {
							indices.push_back(globalToLocal[idxTri[j]]);
						}
					}

					assert(positions.size() == m_vertexCount[idx_layer][i]);
					assert(indices.size() == m_drawCount[idx_layer][i]);

					globalToLocal.clear();
					break;

				case QUAD_IDX:

					for (unsigned int j = 0, idxNow = 0; j < numQuads; ++j) {
						if (*quad[j].GetLayer() == idx_layer) {
							globalToLocal[j] = idxNow;
							idxNow++;
							positions.push_back(*quad[j].GetPos());
							colors.push_back(*quad[j].GetColor());
						}
					}

					for (unsigned int j = 0; j < numIdxQuad; ++j) {
						if (globalToLocal.count(idxQuad[j])) {
							indices.push_back(globalToLocal[idxQuad[j]]);
						}
					}

					assert(positions.size() == m_vertexCount[idx_layer][i]);
					assert(indices.size() == m_drawCount[idx_layer][i]);

					globalToLocal.clear();

					break;

				case CIRCLE_IDX:
				
					for (unsigned int j = 0; j < numCircles; ++j) {
						if (*circle[j].GetLayer() == idx_layer) {
							
							std::vector<glm::vec3> result = generateCircle(*circle[j].GetPos(), *circle[j].GetRadius(), NUM_SEGMENTS);
							positions.insert(positions.end(), result.begin(), result.end());
							
							colors.push_back(*circle[j].GetColorCenter());
							for(unsigned int k = 1;k <= NUM_SEGMENTS; ++k)
								colors.push_back(*circle[j].GetColor());
						}
					}
					assert(positions.size() == m_vertexCount[idx_layer][i]);
					assert(colors.size() == m_vertexCount[idx_layer][i]);

					break;

				default:
					break;
			}

			glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer[idx_layer][i]); // in circle, indices is replaced by radiuses
			if (m_vertexCount[idx_layer][i] > 0) {
				glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[idx_layer][i][POSITION_VB]);
				glBufferData(GL_ARRAY_BUFFER, m_vertexCount[idx_layer][i] * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[idx_layer][i][COLOR_VB]);
				glBufferData(GL_ARRAY_BUFFER, m_vertexCount[idx_layer][i] * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

				if (i != CIRCLE_IDX) {
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[idx_layer][i][INDEX_VB]);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_drawCount[idx_layer][i] * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
				}
			}
			
		}
	}

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	for (unsigned int idx_layer = 0; idx_layer < NUM_LAYERS; ++idx_layer) {
		glDeleteVertexArrays(NUM_MODELS, m_vertexArrayObject[idx_layer]);
	}
}

void Mesh::Draw() {
	for (unsigned int idx_layer = 0; idx_layer < NUM_LAYERS; ++idx_layer) {
		for (unsigned int i = 0; i < NUM_MODELS; ++i) {
			glBindVertexArray(m_vertexArrayObject[idx_layer][i]); // bind

			switch (i) {
				case TRIANGLE_IDX:
					if(m_drawCount[idx_layer][i] > 0) 
						glDrawElements(GL_TRIANGLES, m_drawCount[idx_layer][i], GL_UNSIGNED_INT, 0);
					break;

				case QUAD_IDX:
					if (m_drawCount[idx_layer][i] > 0)
						glDrawElements(GL_QUADS, m_drawCount[idx_layer][i], GL_UNSIGNED_INT, 0);
					break;

				case CIRCLE_IDX:
					if (m_drawCount[idx_layer][i] > 0) {
						//glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_SEGMENTS + 1);
						/*
						vector<GLint> first;
						vector<GLsizei> counts;

						glMultiDrawArrays(GL_TRIANGLE_FAN, first, counts, m_drawCount[idx_layer][i]);
						*/
						for (unsigned int j = 0, now = 0; j < m_drawCount[idx_layer][i]; ++j, now += NUM_SEGMENTS + 1) {
							glDrawArrays(GL_TRIANGLE_FAN, now, now + NUM_SEGMENTS + 1);
						}

					}
						
					break;
				default:
					break;
			}
		}
	}
	glBindVertexArray(0); // unbind
}

std::vector<glm::vec3> generateCircle(glm::vec3 center, float radius, unsigned int SEGMENTS) {
	std::vector<glm::vec3> result;
	result.push_back(center);

	float theta = 2 * acos(-1) / (SEGMENTS - 1);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 
	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = radius;
	float y = 0;

	for (unsigned int i = 0; i < (SEGMENTS - 1); ++i) {
		result.push_back(glm::vec3(x + center.x, y + center.y, 0));
		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}

	result.push_back(glm::vec3(radius + center.x, center.y, 0));
	return result;
}
