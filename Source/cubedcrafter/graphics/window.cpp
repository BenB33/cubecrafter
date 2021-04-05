#include "asserts.h"
#include "window.h"

int Window::windowCount = 0;

Window::Window(int width_, int height_) : width(width_), height(height_)
{
	// If no windows, initialize glfw
	if (windowCount == 0)
	{
		int result = glfwInit();
		CC_ASSERT(result, "ERROR: Initialising GLFW");
	}

	// Create glfw window, error checked
	mainWindow = glfwCreateWindow(width, height, "Cubed Crafter", NULL, NULL);
	CC_ASSERT(mainWindow, "ERROR: Creating window.");

	// make the window current context
	glfwMakeContextCurrent(mainWindow);

	// Initialize glad
	if (windowCount == 0)
	{
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CC_ASSERT(result, "ERROR: Initialising Glad");
	}

	// Get Graphics Card info and print to console (Debug mode only)
	CC_LOG("OpenGL Version: %s",(const char*)glGetString(GL_VERSION));
	CC_LOG("\nGLSL Version: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	CC_LOG("\nGPU: %s %s", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER));


	++windowCount;
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	--windowCount;
	
	if (windowCount == 0) glfwTerminate();
}

void Window::update()
{
	glfwSwapBuffers(mainWindow);
	glfwPollEvents();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Window::setClearColour(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

bool Window::isOpen() const
{
	return !glfwWindowShouldClose(mainWindow);
}

bool Window::isKeyPressed(int keyCode) const
{
	return glfwGetKey(mainWindow, keyCode) == GLFW_PRESS;
}