#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"

int main(int argc, char** argv) {
	Display display(800, 600, "Hello, World!");

	Vertex vertices[] = { 
		Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(1.0f, 0, 0)),
		Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(0, 1.0f, 0)),
		Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(0, 0, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0), glm::vec3(1.0f, 1.0f, 1.0f))

	};
	GLuint elements[] = {
		0, 1, 2,
		1, 2, 3,
		3, 0, 1
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), elements, sizeof(elements) / sizeof(elements[0]));
	Shader shader("./res/basicShader");

	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
	
		shader.Bind();
		mesh.Draw();

		display.Update();
	}
	return 0;
}