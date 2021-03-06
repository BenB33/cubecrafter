#include "entities/camera.h"
#include "entities/entity.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/window.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	Window window;

	window.setClearColour(0.1f, 0.4f, 0.6f, 1.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	float vertices[]
	{// x   y   z
	    0,  0,  1,  // South Face +Z   (0)
		1,  0,  1,  // 
		1,  1,  1,  // 
		0,  1,  1,  // 

		1,  0,  0, // North Face -Z  (4)
		0,  0,  0, //
		0,  1,  0, //
		1,  1,  0, //

		0,  1,  0, // East Face +X (8)
		0,  0,  0, // 
		0,  0,  1, // 
		0,  1,  1, // 
		
		1,  0,  0, // West Face -X (12)
		1,  1,  0, //
		1,  1,  1, //
		1,  0,  1, //

		1,  1,  0, // Top Face -Y (16)
		0,  1,  0, // 
		0,  1,  1, // 
		1,  1,  1, // 

	    0,  0,  0, // Bottom Face +Y (20)
		1,  0,  0, // 
		1,  0,  1, // 
		0,  0,  1, // 
	};

	unsigned int indices[] =
	{
		0, 1,  2,
		0, 2,  3,
		4, 5,  6, 
		4, 6,  7,
		8, 9, 10, 
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23,
	};

	Shader shader("../Resources/Shaders/shader");
	shader.bind();

	Camera camera;
	camera.setPerspective(window.getWidth(), window.getHeight());

	std::shared_ptr<Mesh> squareMesh = std::make_shared<Mesh>(vertices, sizeof(vertices), indices, sizeof(indices));
	Entity squareEntity(squareMesh);
	Entity squareEntity2(squareMesh);
	squareEntity2.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	squareEntity2.setRotation(glm::vec3(0.22f, 0.5f, 0.1f));
	squareEntity2.setPosition(glm::vec3(0.5f, 0.25f, 0));


	float xPos = 0;
	float yPos = 0;
	float zPos = 0;

	float gameTime = 0;

	while (window.isOpen())
	{
		// Clear
		window.clear();

		// Upload Camera to shader
		camera.freeCam(window);
		camera.loadToShader(shader);

		// Logic


		// Render some shit right here
		squareEntity.render(shader);
		squareEntity2.render(shader);

		// Update
		window.update();
	}
}


// For Windows Release Mode, define WinMain
// For removal of console window.
#if defined(CC_PLATFORM_WINDOWS) && defined(CC_BUILD_RELEASE)
int WinMain() { main(); }
#endif // CC_PLATFORM_WINDOWS