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

    


   // SetUniformMat4f(&transform[0][0], "transform", object.Program);


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

        mat4 model;
        mat4 view;
        mat4 projection;

        vec3 axis = {0.5f, 1.0f, 0.0f};
        vec3 move = {0.0f, 0.0f, -5.0f};

        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(projection);

        glm_rotate(model, (float)glfwGetTime(),axis);
        glm_translate(&view[0], move);
        glm_perspective(glm_rad(45.0f), 1200.0f/900.0f, 0.1f, 100.f, projection);

        SetUniformMat4f(&model[0][0], "model", object.Program);
        SetUniformMat4f(&view[0][0],"view", object.Program );
        SetUniformMat4f(&projection[0][0], "projection", object.Program);



    
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
