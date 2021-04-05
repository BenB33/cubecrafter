#include "graphics/window.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "entities/entity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	Window window;

	window.setClearColour(0.1f, 0.4f, 0.6f, 1.0f);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	float vertices[]
	{  // x       y      z
		-0.5f,  -0.5f,  0.0f,  // Bottom Left  (0)
		 0.5f,  -0.5f,  0.0f, // Bottom Right  (1)
		 0.5f,   0.5f,  0.0f, // Top Right     (2)
		-0.5f,   0.5f,  0.0f, // Top Left	   (3)
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};


	std::shared_ptr<Mesh> squareMesh = std::make_shared<Mesh>(vertices, sizeof(vertices), indices, sizeof(indices));
	Entity squareEntity(squareMesh);

	Shader shader("../Resources/Shaders/shader");
	shader.bind();

	float xPos = 0;
	float yPos = 0;
	float zPos = 0;

	float gameTime = 0;

	while (window.isOpen())
	{
		// Clear
		window.clear();

		// Logic
		if (window.isKeyPressed(GLFW_KEY_W))
		{
			squareEntity.setPosition(squareEntity.getPosition() + glm::vec3(0, 0.1f, 0));
		}
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			squareEntity.setPosition(squareEntity.getPosition() + glm::vec3(-0.1f, 0, 0));
		}
		if (window.isKeyPressed(GLFW_KEY_S))
		{
			squareEntity.setPosition(squareEntity.getPosition() + glm::vec3(0, -0.1f, 0));
		}
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			squareEntity.setPosition(squareEntity.getPosition() + glm::vec3(0.1f, 0, 0));
		}

		if (window.isKeyPressed(GLFW_KEY_MINUS))
		{
			squareEntity.setScale(squareEntity.getScale() + glm::vec3(-0.1f, -0.1f,-0.1f));
		}
		if (window.isKeyPressed(GLFW_KEY_EQUAL))
		{
			squareEntity.setScale(squareEntity.getScale() + glm::vec3(0.1f, 0.1f, 0.1f));
		}



		// Render some shit right here
		squareEntity.render(shader);

		// Update
		window.update();
	}
}


// For Windows Release Mode, define WinMain
// For removal of console window.
#if defined(CC_PLATFORM_WINDOWS) && defined(CC_BUILD_RELEASE)
int WinMain() { main(); }
#endif // CC_PLATFORM_WINDOWS