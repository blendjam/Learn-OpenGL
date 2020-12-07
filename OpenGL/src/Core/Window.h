#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Window
{
	GLFWwindow* m_window;
	unsigned int m_height, m_width;
public:
	Window(unsigned int width, unsigned int height);
	void Init();
private:
};

