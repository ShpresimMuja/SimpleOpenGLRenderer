#include "OpenGLUtil.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "stb_image.h"


struct VertexObjects GenrateVertexBuffers(float * vertices, unsigned int size, void(*DataLayout)())
{

    struct VertexObjects VB;
    
    
    glGenVertexArrays(1, &VB.VAO);
    glGenBuffers(1, &VB.VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VB.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VB.VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    DataLayout();

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return VB;


}

unsigned int CompileShader(int ShaderType,const char* const *Source)
{

    unsigned int Shader = glCreateShader(ShaderType);

    glShaderSource(Shader, 1,Source, NULL );

    glCompileShader(Shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %d \n", infoLog );
    }   



    return Shader;

}

unsigned int LinkShaders(unsigned int VertexShader, unsigned int FragmentShader)
{
    unsigned int ShaderProgram = glCreateProgram();
    int success; 
    
    char infoLog[512];


    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %d \n", infoLog );
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);



    return ShaderProgram;


}
char* ReadFile(const char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
    
       fseek(handler, 0, SEEK_END);

       string_size = ftell(handler);
     
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       read_size = fread(buffer, sizeof(char), string_size, handler);

      
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           
           free(buffer);
           buffer = NULL;
       }
       fclose(handler);
    }

    return buffer;
}
void Draw(unsigned int VAO, unsigned int Program, unsigned int VertexNumber)
{
        glUseProgram(Program);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, VertexNumber);


}

void DrawElements(unsigned int VAO, unsigned int Program, unsigned int ElementNumber)
{
        glUseProgram(Program);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,ElementNumber , GL_UNSIGNED_INT, 0);


}

void SetUniform4f(float x, float y, float z, float a, unsigned int Program, const char * UniformName)
{
    int UniformLocation = glGetUniformLocation(Program, UniformName);
    glUseProgram(Program);
    glUniform4f(UniformLocation, x, y, z, a);

}

void SetUniform1i(unsigned int Value, const char * UniformName, unsigned int Program)
{
    glUseProgram(Program);
    glUniform1i(glGetUniformLocation(Program, UniformName), Value);
}





unsigned int LoadTexture(const char * filename)
{
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
int width, height, nrChannels;
unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    printf("Failed to load texture");
}
stbi_image_free(data);

    return texture;
}

unsigned int GenerateElementBuffer(unsigned VAO, int * indices, unsigned int size)
{

    unsigned int VEB;
    glBindVertexArray(VAO);
    glGenBuffers(1, &VEB);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
    

}
void BindTexture(unsigned int texture, int TextureIndex)
{   
    glActiveTexture(GL_TEXTURE0 + TextureIndex);
    glBindTexture(GL_TEXTURE_2D, texture);

}

unsigned int LoadShaders(const char * VertexPath,const char * FragmentPath )
{

    unsigned int Program;

    const char * vertexSource = ReadFile(VertexPath);
   
    const char * fragmentSource = ReadFile(FragmentPath);
   
    
    unsigned int Vertex =  CompileShader(GL_VERTEX_SHADER, &vertexSource);
    unsigned int Fragment = CompileShader(GL_FRAGMENT_SHADER, &fragmentSource);

    
    return LinkShaders(Vertex, Fragment);


}