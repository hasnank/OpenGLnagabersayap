#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"

int main(int argc, char** argv) {
	Display display(800, 800, "Hello, World!");

	Vertex vertices[] = { 
		Vertex(glm::vec3(-0.828000f, 0.006000f, 0), glm::vec3(0.402344f, 0.773438f, 0.410156f)),
		Vertex(glm::vec3(-0.734000f, 0.038000f, 0), glm::vec3(0.449219f, 0.316406f, 0.996094f)),
		Vertex(glm::vec3(-0.868000f, 0.234000f, 0), glm::vec3(0.289062f, 0.921875f, 0.160156f)),
		Vertex(glm::vec3(-0.582000f, -0.134000f, 0), glm::vec3(0.800781f, 0.726562f, 0.667969f)),
		Vertex(glm::vec3(-0.624000f, 0.140000f, 0), glm::vec3(0.945312f, 0.980469f, 0.886719f)),
		Vertex(glm::vec3(-0.400000f, 0.526000f, 0), glm::vec3(0.273438f, 0.484375f, 0.757812f)),
		Vertex(glm::vec3(-0.178000f, 0.276000f, 0), glm::vec3(0.328125f, 0.968750f, 0.105469f)),
		Vertex(glm::vec3(-0.406000f, 0.052000f, 0), glm::vec3(0.906250f, 0.902344f, 0.550781f)),
		Vertex(glm::vec3(-0.210000f, 0.046000f, 0), glm::vec3(0.460938f, 0.351562f, 0.179688f)),
		Vertex(glm::vec3(-0.098000f, 0.456000f, 0), glm::vec3(0.386719f, 0.199219f, 0.621094f)),
		Vertex(glm::vec3(-0.050000f, 0.426000f, 0), glm::vec3(0.785156f, 0.601562f, 0.398438f)),
		Vertex(glm::vec3(-0.006000f, 0.510000f, 0), glm::vec3(0.195312f, 0.050781f, 0.714844f)),
		Vertex(glm::vec3(0.044000f, 0.470000f, 0), glm::vec3(0.191406f, 0.343750f, 0.636719f)),
		Vertex(glm::vec3(0.096000f, 0.488000f, 0), glm::vec3(0.351562f, 0.144531f, 0.363281f)),
		Vertex(glm::vec3(0.128000f, 0.382000f, 0), glm::vec3(0.019531f, 0.089844f, 0.343750f)),
		Vertex(glm::vec3(-0.086000f, -0.034000f, 0), glm::vec3(0.910156f, 0.367188f, 0.828125f)),
		Vertex(glm::vec3(0.006000f, 0.190000f, 0), glm::vec3(0.667969f, 0.695312f, 0.800781f)),
		Vertex(glm::vec3(0.100000f, 0.012000f, 0), glm::vec3(0.773438f, 0.605469f, 0.703125f)),
		Vertex(glm::vec3(0.058000f, -0.070000f, 0), glm::vec3(0.328125f, 0.066406f, 0.054688f)),
		Vertex(glm::vec3(0.188000f, -0.014000f, 0), glm::vec3(0.507812f, 0.453125f, 0.253906f)),
		Vertex(glm::vec3(0.274000f, 0.084000f, 0), glm::vec3(0.128906f, 0.238281f, 0.859375f)),
		Vertex(glm::vec3(0.302000f, 0.352000f, 0), glm::vec3(0.527344f, 0.437500f, 0.910156f)),
		Vertex(glm::vec3(0.326000f, 0.606000f, 0), glm::vec3(0.242188f, 0.628906f, 0.253906f)),
		Vertex(glm::vec3(0.534000f, 0.134000f, 0), glm::vec3(0.878906f, 0.984375f, 0.402344f)),
		Vertex(glm::vec3(0.388000f, 0.014000f, 0), glm::vec3(0.242188f, 0.003906f, 0.492188f)),
		Vertex(glm::vec3(0.860000f, 0.304000f, 0), glm::vec3(0.589844f, 0.914062f, 0.859375f)),
		Vertex(glm::vec3(0.958000f, 0.242000f, 0), glm::vec3(0.417969f, 0.585938f, 0.558594f)),
		Vertex(glm::vec3(0.872000f, 0.230000f, 0), glm::vec3(0.218750f, 0.359375f, 0.164062f)),
		Vertex(glm::vec3(0.818000f, -0.018000f, 0), glm::vec3(0.921875f, 0.687500f, 0.230469f)),
		Vertex(glm::vec3(0.736000f, 0.044000f, 0), glm::vec3(0.980469f, 0.195312f, 0.683594f)),
		Vertex(glm::vec3(0.582000f, -0.118000f, 0), glm::vec3(0.234375f, 0.328125f, 0.921875f)),
		Vertex(glm::vec3(0.626000f, 0.142000f, 0), glm::vec3(0.093750f, 0.855469f, 0.359375f)),
		Vertex(glm::vec3(0.130000f, -0.350000f, 0), glm::vec3(0.007812f, 0.101562f, 0.992188f)),
		Vertex(glm::vec3(0.216000f, -0.394000f, 0), glm::vec3(0.261719f, 0.980469f, 0.976562f)),
		Vertex(glm::vec3(0.164000f, -0.484000f, 0), glm::vec3(0.664062f, 0.226562f, 0.980469f)),
		Vertex(glm::vec3(0.198000f, -0.544000f, 0), glm::vec3(0.160156f, 0.816406f, 0.898438f)),
		Vertex(glm::vec3(0.078000f, -0.626000f, 0), glm::vec3(0.019531f, 0.234375f, 0.484375f)),
		Vertex(glm::vec3(0.082000f, -0.672000f, 0), glm::vec3(0.578125f, 0.457031f, 0.843750f)),
		Vertex(glm::vec3(-0.022000f, -0.674000f, 0), glm::vec3(0.742188f, 0.378906f, 0.535156f)),



	};
	GLuint elements[] = {
		0, 1, 2,
		1, 2, 4,
		1, 3, 4,
		2, 4, 5,
		4, 5, 6,
		4, 7, 6,
		6, 7, 8,
		6, 8, 15,
		6, 16, 15,
		16, 15, 17,
		15, 17, 18,
		6, 10, 16,
		6, 9, 10,
		9, 10, 11,
		10, 11, 12,
		11, 12, 13,
		12, 13, 14,
		15, 18, 32,
		18, 32, 33,
		32, 33, 34,
		33, 34, 35,
		34, 35, 36,
		35, 36, 37,
		36, 37, 38,
		16, 17, 20,
		17, 19, 20,
		16, 20, 21,
		20, 23, 24,
		20, 21, 23,
		21, 22, 25,
		21, 23, 25,
		23, 25, 31,
		25, 27, 31,
		25, 26, 27,
		27, 29, 31,
		27, 28, 29,
		29, 30, 31
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