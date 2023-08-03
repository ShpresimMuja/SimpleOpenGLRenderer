#pragma once 
#include <stdio.h>
#include <glad/glad.h>
#include <glfw3.h>

typedef  struct Window 
{
    GLFWwindow * window;
    
    int created; 
} Window;



int initiliseWindow(struct Window * window, int Width, int Height, const char* Name);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

