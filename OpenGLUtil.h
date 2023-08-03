#pragma once 


typedef struct VertexObjects
{
    unsigned int VAO;
    unsigned int VBO;
};
//reads files and returns a pointer to a dynamically allocated batch of memory
//must be deleted after use.
char * ReadFile(const char * filename);
//generates a Vertex Array Object and a Vertex Buffer Object based on data given.
struct VertexObjects GenrateVertexBuffers(float * vertices, unsigned int size, void(*DataLayout)());
unsigned int GenerateElementBuffer(unsigned VAO, int * indices, unsigned int size);


//compiles the shader given a shader type and a char * source likely read from file.
unsigned int CompileShader(int ShaderType,const char* const *Source);


//links the shaders and returns a shader program.
unsigned int LinkShaders(unsigned int VertexShader, unsigned int FragmentShader);




void Draw(unsigned int VAO, unsigned int Program, unsigned int VertexNumber);


void DrawElements(unsigned int VAO, unsigned int Program, unsigned int ElementNumber);



void SetUniform4f(float x, float y, float z, float a, unsigned int Program, const char * UniformName);
void SetUniform1i(unsigned int Value, const char * UniformName, unsigned int Program);


void SetDataAtributes(int index, int vertexRow, int Datarow, void* stride);


unsigned int LoadTexture(const char * filename);

void BindTexture(unsigned int texture, int TextureIndex);

unsigned int LoadShaders(const char * VertexPath,const char * FragmentPath );