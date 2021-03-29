#ifndef CUBEDCRAFTER_GRAPHICS_WINDOW_H_ // Pragma once
#define CUBEDCRAFTER_GRAPHICS_WINDOW_H_

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
	bool isOpen() const;
};

#endif // CUBEDCRAFTER_GRAPHICS_WINDOW_H_