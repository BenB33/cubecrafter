#ifndef CUBEDCRAFTER_GRAPHICS_WINDOW_H_ // Pragma once
#define CUBEDCRAFTER_GRAPHICS_WINDOW_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* mainWindow;
	static int windowCount;

public:
	Window();
	~Window();

	void update();
	void clear();
	bool isOpen() const;
};

#endif // CUBEDCRAFTER_GRAPHICS_WINDOW_H_