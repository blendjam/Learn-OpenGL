#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
class Texture
{
private:
	unsigned int m_ID;
public:
	Texture(const std::string& imagePath, bool isAlpha = false);
	~Texture();
	void bind(unsigned int slot = 0);
	void unbind();

};
#endif // !TEXTURE_H

