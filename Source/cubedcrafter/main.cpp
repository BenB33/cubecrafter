#include "graphics/window.h"

int main()
{
	Window window;

	window.setClearColour(0.1f, 0.4f, 0.6f, 1.0f);

	GLfloat vertices[]
	{  // x       y      z
		-0.5f,  -0.5f,  0.0f,
		 0.5f,  -0.5f,  0.0f,
		 0.0f,   0.5f,  0.0f
	};

	GLuint vbo_id, vao_id;

	// Binding Buffers
	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Binding Vertex Array
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), nullptr);

	while (window.isOpen())
	{
		// Clear
		window.clear();

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Update
		window.update();
	}
}


// For Windows Release Mode, define WinMain
// For removal of console window.
#if defined(CC_PLATFORM_WINDOWS) && defined(CC_BUILD_RELEASE)
int WinMain() { main(); }
#endif // CC_PLATFORM_WINDOWS