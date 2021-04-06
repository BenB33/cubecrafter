#ifndef CUBEDCRAFTER_GRAPHICS_WINDOW_H_ // Pragma once
#define CUBEDCRAFTER_GRAPHICS_WINDOW_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* mainWindow;
	static int windowCount;
	int width, height;
	bool isMouseLocked = false;

	double mouseX, mouseY, lastMouseX, lastMouseY;

	static void onWindowResize(GLFWwindow* window, int width, int height);

public:
	Window(int width_ = 1280, int height_ = 720);
	~Window();

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void update();
	void clear();
	void setClearColour(float r, float g, float b, float a) const;
	bool isOpen() const;

	bool isKeyPressed(int keyCode) const;
	void setMouseLock(bool lockStatus);
	bool getIsMouseLocked() const;
	void toggleMouseLock();

	float getMouseDeltaX() const;
	float getMouseDeltaY() const;
};

#endif // CUBEDCRAFTER_GRAPHICS_WINDOW_H_