#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 600
#define HEIGHT 600

int main(int argc, char** argv) {
	Display display(WIDTH, HEIGHT, "3D!");

	Vertex vertices[] = {
		//depan
		Vertex(glm::vec3(0.346, 0.723, 0.0365), glm::vec2(0.41, 0.107), glm::vec3(0,0,1)),
		Vertex(glm::vec3(-0.346, 0.723, 0.0365),  glm::vec2(0.161, 0.107), glm::vec3(0,0,1)),
		Vertex(glm::vec3(-0.346, -0.723, 0.0365),  glm::vec2(0.161, 0.615), glm::vec3(0,0,1)),
		Vertex(glm::vec3(0.346, -0.723, 0.0365),  glm::vec2(0.41, 0.615), glm::vec3(0,0,1)),
		//belakang
		Vertex(glm::vec3(0.346, 0.723, -0.0365), glm::vec2(0.836, 0.107), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(-0.346, 0.723, -0.0365),  glm::vec2(0.617, 0.107), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(-0.346, -0.723, -0.0365),  glm::vec2(0.617, 0.615), glm::vec3(0,0,-1)),
		Vertex(glm::vec3(0.346, -0.723, -0.0365),  glm::vec2(0.836, 0.615), glm::vec3(0,0,-1)),
		//atas
		Vertex(glm::vec3(0.346, 0.723, 0.0365), glm::vec2(0.672, 0.066), glm::vec3(0,1,0)),
		Vertex(glm::vec3(-0.346, 0.723, 0.0365),  glm::vec2(0.283, 0.066), glm::vec3(0,1,0)),
		Vertex(glm::vec3(-0.346, 0.723, -0.0365),  glm::vec2(0.283, 0.031), glm::vec3(0,1,0)),
		Vertex(glm::vec3(0.346, 0.723, -0.0365), glm::vec2(0.672, 0.031), glm::vec3(0,1,0)),
		//bawah
		Vertex(glm::vec3(-0.346, -0.723, 0.0365),  glm::vec2(0.283, 0.791), glm::vec3(0,-1,0)),
		Vertex(glm::vec3(0.346, -0.723, 0.0365),  glm::vec2(0.664, 0.791), glm::vec3(0,-1,0)),
		Vertex(glm::vec3(0.346, -0.723, -0.0365),  glm::vec2(0.664, 0.832), glm::vec3(0,-1,0)),
		Vertex(glm::vec3(-0.346, -0.723, -0.0365),  glm::vec2(0.283, 0.832), glm::vec3(0,-1,0)),
		//kanan
		Vertex(glm::vec3(0.346, 0.723, 0.0365), glm::vec2(0.06, 0.723), glm::vec3(1,0,0)),
		Vertex(glm::vec3(0.346, -0.723, 0.0365),  glm::vec2(0.904, 0.723), glm::vec3(1,0,0)),
		Vertex(glm::vec3(0.346, -0.723, -0.0365),  glm::vec2(0.904, 0.686), glm::vec3(1,0,0)),
		Vertex(glm::vec3(0.346, 0.723, -0.0365), glm::vec2(0.06, 0.686), glm::vec3(1,0,0)),
		//kiri
		Vertex(glm::vec3(-0.346, 0.723, 0.0365),  glm::vec2(0.893, 0.97), glm::vec3(-1,0,0)),
		Vertex(glm::vec3(-0.346, -0.723, 0.0365),  glm::vec2(0.063, 0.97), glm::vec3(-1,0,0)),
		Vertex(glm::vec3(-0.346, -0.723, -0.0365),  glm::vec2(0.063, 0.934), glm::vec3(-1,0,0)),
		Vertex(glm::vec3(-0.346, 0.723, -0.0365),  glm::vec2(0.893, 0.934), glm::vec3(-1,0,0)),
	};

	unsigned int indices[] = {
		//depan
		0, 1, 2, 3,
		//belakang
		4, 5, 6, 7,
		//atas
		8, 9, 10, 11,
		//bawah
		12, 13, 14, 15,
		//kanan
		16, 17, 18, 19,
		//kiri
		20, 21, 22, 23,
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh2("./res/monkey3.obj");

	Shader shader("./res/basicShader");
	Texture texture("./res/Untitled-1.png");
	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.GetPos().x = sinCounter;
		transform.GetPos().z = cosCounter;
		transform.GetRot().x = counter*2;
		transform.GetRot().y = counter;
		//transform.GetRot().z = counter;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform,camera);
		mesh.Draw();

		display.Update();
		counter += 0.0005f;
	}
	return 0;
}