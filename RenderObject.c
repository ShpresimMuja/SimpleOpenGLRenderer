#include "RenderObject.h"
#include "glad/glad.h"


RenderObject CreateRenderObject(float * vertices, unsigned int size, void (*DataLayout)())
{
    RenderObject object;

    object.VB = GenrateVertexBuffers(vertices, size, DataLayout);


    return object;

}



void DataLayout()
{
      // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  


}