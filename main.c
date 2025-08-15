#include "shaders.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow* opengl_initialization();

int main()
{
	GLFWwindow* window = opengl_initialization();
	if (!window)
	{
		return -1;
	}

	const char* vertex_path = "shaders/vertex.glsl";
	const char* fragment_path = "shaders/fragment.glsl";
	char* fragment_source = get_shader_source(fragment_path);
	char* vertex_source = get_shader_source(vertex_path);

	// printf("%s%s\n", vertex_source, fragment_source);
	unsigned int program = get_program(vertex_source, fragment_source);
	printf("%u", program);

	free(vertex_source);
	free(fragment_source);
	vertex_source = NULL;
	fragment_source = NULL;


	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

GLFWwindow* opengl_initialization()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    	GLFWwindow* window = glfwCreateWindow(640, 480, "a", NULL, NULL);
    	if (!window)
	{
        	printf("Failed to create GLFW window\n");
        	glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    	{
        	printf("Failed to initialize GLAD");
        	return NULL;
	}

	return window;
}

