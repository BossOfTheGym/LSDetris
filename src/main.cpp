#include <cmath>
#include <string>
#include <iostream>

#define GL_HEADER_INCLUDED
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE

GLuint create_shader(GLenum type, const GLchar *source, GLint size)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, &size);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cerr << "Failed to compile shader" << std::endl;
		std::abort();
	}

	return shader;
}

template<class ... shader_t>
GLuint create_program(shader_t ... shaders)
{
	GLuint program = glCreateProgram();
	(glAttachShader(program, shaders), ...);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		std::cerr << "Failed to create program" << std::endl;
		std::abort();
	}

	(glDetachShader(program, shaders), ...);

	return program;
}

std::string VERTEX_SRC = R"shader_source(
#version 460 core

const vec2 POSITIONS[4] = {
	vec2(+1.0, +1.0), vec2(+1.0, -1.0), vec2(-1.0, -1.0), vec2(-1.0, +1.0)
};

void main()
{
	gl_Position = vec4(POSITIONS[gl_VertexID % 4], 0.0, 1.0);
}
)shader_source";

std::string FRAGMENT_SRC = R"shader_source(
#version 460 core

out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
)shader_source";

GLuint create_shader_program()
{
	GLuint vert_shader = create_shader(GL_VERTEX_SHADER, VERTEX_SRC.c_str(), VERTEX_SRC.size());
	GLuint frag_shader = create_shader(GL_FRAGMENT_SHADER, FRAGMENT_SRC.c_str(), FRAGMENT_SRC.size());
	GLuint program = create_program(vert_shader, frag_shader);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	return program;
}

struct gfx_resources {
	gfx_resources() {
		glCreateVertexArrays(1, &dummy_vao);
		shader_program = create_shader_program();
	}

	~gfx_resources()
	{
		glDeleteVertexArrays(1, &dummy_vao);
		glDeleteProgram(shader_program);
	}

	GLuint dummy_vao{};
	GLuint shader_program{};
};

void mainloop(GLFWwindow *window)
{
	// create resources
	gfx_resources resources;

	// mainloop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		double t = glfwGetTime();

		glClearColor(1.0, (std::cos(t) + 1.0) / 2.0, (std::sin(t) + 1.0) / 2.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glUseProgram(resources.shader_program);
		glBindVertexArray(resources.dummy_vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glfwSwapBuffers(window);
	}
}

int main(int argc, char *argv[])
{
	// init glfw
	if (!glfwInit()) {
		std::cout << "We are fucked!!!" << std::endl;
		return -1;
	}

	// create window	
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(400, 800, "LSDetris", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		return -1;
	}
	glfwSetWindowUserPointer(window, nullptr);
	glfwMakeContextCurrent(window);

	// OpenGL functions
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize glew" << std::endl;
		return -1;
	}

	// mainloop
	mainloop(window);

	// destroy window
	glfwDestroyWindow(window);

	// terminate lib
	glfwTerminate();

	return 0;
}