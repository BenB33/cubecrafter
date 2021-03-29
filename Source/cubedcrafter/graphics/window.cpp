#include "window.h"

#include <iostream>

int Window::windowCount = 0;

Window::Window()
{
	// If no windows, initialize glfw
	if (windowCount == 0) if (!glfwInit()) std::cerr << "Error Initalizing glfw\n";

	// Create glfw window, error checked
	mainWindow = glfwCreateWindow(1280, 720, "Cubed Crafter", NULL, NULL);
	if (!mainWindow) std::cerr << "Error Creating window\n";

	// make the window current context
	glfwMakeContextCurrent(mainWindow);

	// Initialize glad
	if (windowCount == 0) if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cerr << "Error initalizing glad\n";
	
	++windowCount;
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

bool Window::isOpen() const
{
	return !glfwWindowShouldClose(mainWindow);
}