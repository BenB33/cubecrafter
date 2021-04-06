#include "asserts.h"
#include "window.h"

#include <algorithm>

int Window::windowCount = 0;

void centerWindow(GLFWwindow* window);
void onGLFWError(int errorCode, const char* message);
void onKeyEvent(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);

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
	centerWindow(mainWindow);

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

	// vsync on by default
	glfwSwapInterval(1);

	// Set callbacks
	glfwSetWindowUserPointer(mainWindow, this);
	glfwSetFramebufferSizeCallback(mainWindow, onWindowResize);
	glfwSetErrorCallback(onGLFWError);
	glfwSetKeyCallback(mainWindow, onKeyEvent);
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	--windowCount;
	
	if (windowCount == 0) glfwTerminate();
}

void Window::update()
{
	// Swap buffers (go to next frame)
	glfwSwapBuffers(mainWindow);

	// Check for input events such as keyboard presses and mouse movement
	glfwPollEvents();

	// Update mouse position
	lastMouseX = mouseX;
	lastMouseY = mouseY;
	glfwGetCursorPos(mainWindow, &mouseX, &mouseY);
}


float Window::getMouseDeltaX() const
{
	return lastMouseX - mouseX;
}
float Window::getMouseDeltaY() const
{
	return lastMouseY - mouseY;
}

bool Window::getIsMouseLocked() const
{
	return isMouseLocked;
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



void Window::onWindowResize(GLFWwindow* window, int newWidth, int newHeight)
{
	Window* userPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	userPtr->width = newWidth;
	userPtr->height = newHeight;
	glViewport(0, 0, newWidth, newHeight);
}



void Window::setMouseLock(bool lockStatus)
{
	isMouseLocked = lockStatus;
	int cursorMode = GLFW_CURSOR_NORMAL;
	if (isMouseLocked)
	{
		cursorMode = GLFW_CURSOR_DISABLED;
	}
	glfwSetInputMode(mainWindow, GLFW_CURSOR, cursorMode);
}

void Window::toggleMouseLock()
{
	setMouseLock(!isMouseLocked);
}


// Key typed callback
void onKeyEvent(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
	if (keyCode == GLFW_KEY_E || keyCode == GLFW_KEY_ESCAPE)
	{
		if (action == GLFW_PRESS)
		{
			Window* userPtr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
			userPtr->toggleMouseLock();
		}
	}
}

// GLFW Errors
void onGLFWError(int errorCode, const char* message)
{
	CC_ASSERT(false, message);
}


// On a multi-monitor setup, find the monitor that the glfw window is mostly on
// Used to center a window relative to that monitor
GLFWmonitor* findCurrentMonitor(GLFWwindow* window) {
	int monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

	if (!monitors) {
		CC_ASSERT(false, "No monitors detected");
		return nullptr;
	}

	int window_x, window_y, window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);
	glfwGetWindowPos(window, &window_x, &window_y);

	GLFWmonitor* best_monitor = nullptr;
	int best_area = 0;

	for (int i = 0; i < monitor_count; ++i) {
		GLFWmonitor* monitor = monitors[i];

		int monitor_x, monitor_y;
		glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (!mode) continue;

		int area_min_x = std::max(window_x, monitor_x);
		int area_min_y = std::max(window_x, monitor_y);

		int area_max_x = std::min(window_x + window_width, monitor_x + mode->width);
		int area_max_y = std::min(window_x + window_height, monitor_x + mode->height);

		int area = (area_max_x - area_min_x) * (area_max_y - area_min_y);

		if (area > best_area) {
			best_area = area;
			best_monitor = monitor;
		}
	}

	return best_monitor;
}

// Center a glfw window relative to the monitor it mostly occupies
static void centerWindow(GLFWwindow* window) {
	GLFWmonitor* current_monitor = findCurrentMonitor(window);
	const GLFWvidmode* mode = glfwGetVideoMode(current_monitor);
	if (!mode) return;

	int monitor_x, monitor_y;
	glfwGetMonitorPos(current_monitor, &monitor_x, &monitor_y);

	int window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);

	glfwSetWindowPos(window,
		monitor_x + (mode->width - window_width) / 2,
		monitor_y + (mode->height - window_height) / 2);
}