#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	if (!glfwInit()) std::cerr << "Error Initalizing glfw\n";

	GLFWwindow* main_window = glfwCreateWindow(1280, 720, "Cubed Crafter", NULL, NULL);

	if (!main_window) std::cerr << "Error Creating window\n";

	while (!glfwWindowShouldClose(main_window))
	{
		
	}

	glfwDestroyWindow(main_window);
	glfwTerminate();
}