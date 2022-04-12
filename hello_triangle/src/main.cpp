#include <iostream>

#include <GLFW/glfw3.h>

int main() {
    try {
        if (!glfwInit()) throw std::runtime_error("GLFW initialization failed.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const auto window = glfwCreateWindow(800, 600, "Hello triangle", nullptr, nullptr);

        if (!window) throw std::runtime_error("Window creation failed.");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    catch (const std::exception error) {
        std::cerr << error.what() << std::endl;

        throw;
    }

    std::cout << "done" << std::endl;

    return 0;
}
