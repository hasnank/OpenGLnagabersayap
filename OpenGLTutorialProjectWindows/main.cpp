//
//  main1.cpp
//  tesOpenGL
//
//  Created by Dharma Kurnia Septialoka on 4/10/17.
//  Copyright © 2017 Dharma Kurnia Septialoka. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

int main(int argc, char** argv) {
	Display display(800, 600, "Hello, World!");

	Vertex triangles[] = {
		Vertex(glm::vec3(-0.1f, -0.5f, 0), glm::vec3(0.0f, 0.941406f, 0.0f), 2),
		Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0.0f, 0.507812f, 0.0f), 2),
		Vertex(glm::vec3(-0.3f, -0.1f, 0), glm::vec3(0.0f, 0.992188f, 0.0f), 2),
		Vertex(glm::vec3(-0.1f, -0.2f, 0), glm::vec3(0.0f, 0.593750f, 0.0f), 2),
		Vertex(glm::vec3(-0.5f, -0.2f, 0), glm::vec3(0.0f, 0.882812f, 0.0f), 2),
		Vertex(glm::vec3(-0.3f, 0.2f, 0), glm::vec3(0.0f, 0.089844f, 0.0f), 2),
		Vertex(glm::vec3(-0.1f, 0.1f, 0), glm::vec3(0.0f, 0.328125f, 0.0f), 2),
		Vertex(glm::vec3(-0.5f, 0.1f, 0), glm::vec3(0.0f, 0.175781f, 0.0f), 2),
		Vertex(glm::vec3(-0.3f, 0.4f, 0), glm::vec3(0.0f, 0.957031f, 0.0f), 2),
	};

	Vertex quads[] = {
		//ini background (layer 0)
		Vertex(glm::vec3(-1.0, -1.0, -1.0),  glm::vec3(0.8, 0.9, 1.0), 0),
		Vertex(glm::vec3(-1.0, 1.0, -1.0),  glm::vec3(0.5, 0.7, 1.0), 0),
		Vertex(glm::vec3(1.0, 1.0, -1.0),  glm::vec3(0.5, 0.7, 1.0), 0),
		Vertex(glm::vec3(1.0, -1.0, -1.0),  glm::vec3(0.8, 0.9, 1.0), 0),
		Vertex(glm::vec3(-0.25, -1, 0), glm::vec3(0.5, 0.25, 0.0), 2),
		Vertex(glm::vec3(-0.25, -0.5, 0),  glm::vec3(0.6, 0.3, 0.0), 2),
		Vertex(glm::vec3(-0.35, -0.5, 0),  glm::vec3(0.6, 0.3, 0.0), 2),
		Vertex(glm::vec3(-0.35, -1, 0),  glm::vec3(0.5, 0.25, 0.0), 2),
		
	};

	Circle circle[] = {
		Circle(glm::vec3(0.5, 0.5, 0), glm::vec3(0,0,0), 0.4, 2)
	};

	GLuint triangleElmt[] = {
		0,1,2,
		3,4,5,
		6,7,8
	};

	GLuint quadsElmt[] = {
		0,1,2,3,
		4,5,6,7
	};


	Mesh mesh(triangles, sizeof(triangles) / sizeof(triangles[0]), 
		triangleElmt, sizeof(triangleElmt) / sizeof(triangleElmt[0]), 
		quads, sizeof(quads) / sizeof(quads[0]), 
		quadsElmt, sizeof(quadsElmt) / sizeof(quadsElmt[0]),
 circle, sizeof(circle) / sizeof(circle[0]));


	//    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	// Texture texture("./res/bricks.jpg");


	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();
		mesh.Draw();
		display.Update();
	}
	return 0;
}
