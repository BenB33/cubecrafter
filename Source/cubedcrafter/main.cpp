#include "graphics/window.h"
#include "graphics/mesh.h"

int main()
{
	Window window;

	window.setClearColour(0.1f, 0.4f, 0.6f, 1.0f);

	float vertices[]
	{  // x       y      z
		-0.5f,   0.5f,  0.0f, // Top Left	  (0)
		 0.5f,   0.5f,  0.0f, // Top Right    (1)
		 0.5f,  -0.5f,  0.0f, // Bottom Right (2)
		-0.5f,  -0.5f,  0.0f,  // Bottom Left  (3)
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
	};


	Mesh squareMesh(vertices, sizeof(vertices), indices, sizeof(indices));

	while (window.isOpen())
	{
		// Clear
		window.clear();

		// Render some shit right here
		squareMesh.render();

		// Update
		window.update();
	}
}


// For Windows Release Mode, define WinMain
// For removal of console window.
#if defined(CC_PLATFORM_WINDOWS) && defined(CC_BUILD_RELEASE)
int WinMain() { main(); }
#endif // CC_PLATFORM_WINDOWS