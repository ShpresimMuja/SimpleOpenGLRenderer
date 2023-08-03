#include <glad/glad.h>
#include <glfw3.h>
#include "Window.h"
#include <stdio.h>
#include <stdlib.h>
#include "OpenGLUtil.h"
#include "stb_image.h"
#include "cglm/cglm.h"
#include "Utils.h"
#include "RenderObject.h"




 

    


int main()
{

    Window window;
    initiliseWindow(&window, 1200, 900, "App");

    RenderObject object;

    object.Program = LoadShaders("vertex.glsl", "fragment.glsl");
    
    object.VB = GenrateVertexBuffers(vertices, sizeof(vertices), DataLayout);
  

    unsigned int texture = LoadTexture("textures/wall.jpg");

    unsigned int TextureIndex = 0;
    SetUniform1i(TextureIndex, "texture1",object.Program);

    mat4 transform;
    vec3 vec = {0.4f, 1.0f,1.0f };
    vec3 vec1 = {0.5f, 0.5f, 0.5f};
    vec3 trans = {0.5f, -0.5f, 0.0f};
    


    glm_mat4_identity(transform);

    glm_rotate(transform, glm_rad(45.0f), vec);
    glm_scale(transform,vec1);

    


    SetUniformMat4f(&transform[0][0], "transform", object.Program);


    printf(glGetString(GL_VERSION));
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.window))
    {
        // input
        // -----
        processInput(window.window);

        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    
        BindTexture(texture, TextureIndex);
        Draw(object.VB.VAO, object.Program, 36);
      
        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
