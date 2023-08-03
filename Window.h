#pragma once 
#include <stdio.h>
#include <glfw3.h>

struct Window 
{
    GLFWwindow * window;

    int created; 
};



int initiliseWindow(struct Window * window, int Width, int Height, const char* Name);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

