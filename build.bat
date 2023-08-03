gcc -m64  -D GLFW_DLL -I glad/include -I GLFW/ -I cglm/ main.c glad/src/glad.c Window.c OpenGLUtil.c stb_image.c -o main ./cglm.dll ./glfw3.dll -lopengl32 -lgdi32 -lkernel32 -lglu32 && main.exe
