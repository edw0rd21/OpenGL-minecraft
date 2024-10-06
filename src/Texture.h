#pragma once
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    void loadTexture(std::string& filePath);
    void bindTexture(GLenum texUnit);

private:
    unsigned int texID;
    int width, height, nrChannels;
};

