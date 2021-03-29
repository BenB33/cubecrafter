#include "graphics/window.h";
#include <glad/glad.h>

int main()
{
	Window window;

	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

	while (window.isOpen())
	{
		// do logic
		window.clear();

		window.update();
	}
}