#include <iostream>

#include <GLFW/glfw3.h>

template<class ... args_t>
auto sum(args_t&& ... args)
{
	return (args + ...); 
}

int main(int argc, char *argv[])
{
	GLFWwindow* window = nullptr;
	if (!glfwInit()) {
		std::cout << "We are fucked!!!" << std::endl;
		return 1;
	} else {
		std::cout << "Okay, we are not" << std::endl;
	}
	std::cout << "Hello my fellow nigga" << std::endl;
	std::cout << "The ultimate answer of the universe is " << sum(1, 2, 3, 4, 5, 4.5, 5.5, 25) << std::endl;
	return 0;
}