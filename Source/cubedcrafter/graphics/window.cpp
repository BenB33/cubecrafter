#include "window.h"

#include "asserts.h"

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