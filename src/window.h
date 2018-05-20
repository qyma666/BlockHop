#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <glfw/glfw3.h>

class Window
{
public:
	Window();
	Window(const char* title, int width, int height);
	~Window();

	GLFWwindow* glfwWindow;
	int width, height;
	const char* title;

	void destroy();
	void createGLFWWindow();
	void cursorMode(int mode);
};

#endif // WINDOW_H_INCLUDED
