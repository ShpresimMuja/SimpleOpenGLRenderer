#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1)  in vec3 aColour;// the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 ourColour;
out vec2 TexCoord;


void main()
{
    gl_Position = projection * view * model *  vec4(aPos, 1.0);; // see how we directly give a vec3 to vec4's constructor
   // ourColour = aColour;
    TexCoord = aTexCoord;
}