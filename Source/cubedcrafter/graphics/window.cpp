#include "window.h"

#include <iostream>

int Window::windowCount = 0;

Window::Window()
{
	if (windowCount == 0) if (!glfwInit()) std::cerr << "Error Initalizing glfw\n";


	mainWindow = glfwCreateWindow(1280, 720, "Cubed Crafter", NULL, NULL);
	windowCount++;
	if (!mainWindow) std::cerr << "Error Creating window\n";
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	windowCount--;
	
	if (windowCount == 0) glfwTerminate();
}

void Window::update()
{

}

bool Window::isOpen() const
{
	return !glfwWindowShouldClose(mainWindow);
}



