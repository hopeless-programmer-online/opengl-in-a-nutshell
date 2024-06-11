#include <string>
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>

int main() {
    try {
        if (!glfwInit()) throw std::runtime_error("GLFW initialization failed.");

        const auto window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);

        if (!window) throw std::runtime_error("Window creation failed.");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    catch (std::runtime_error error) {
        std::cerr << error.what() << std::endl;

        throw;
    }

    std::cout << "done" << std::endl;

    return 0;
}
