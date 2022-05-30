#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
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

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) throw std::runtime_error("GLEW initialization failed.");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            int width, height;

            glfwGetFramebufferSize(window, &width, &height);

            glViewport(0, 0, width, height);
            glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();

            glfwSwapBuffers(window);
        }

        auto error = glGetError();

        if (error != GL_NO_ERROR) {
            if (error == GL_INVALID_ENUM) throw std::runtime_error("GL_INVALID_ENUM");
            if (error == GL_INVALID_VALUE) throw std::runtime_error("GL_INVALID_VALUE");
            if (error == GL_INVALID_OPERATION) throw std::runtime_error("GL_INVALID_OPERATION");
            if (error == GL_INVALID_FRAMEBUFFER_OPERATION) throw std::runtime_error("GL_INVALID_FRAMEBUFFER_OPERATION");
            if (error == GL_OUT_OF_MEMORY) throw std::runtime_error("GL_OUT_OF_MEMORY");
            if (error == GL_STACK_UNDERFLOW) throw std::runtime_error("GL_STACK_UNDERFLOW");
            if (error == GL_STACK_OVERFLOW) throw std::runtime_error("GL_STACK_OVERFLOW");

            throw std::runtime_error("Unknown OpenGL error: " + std::to_string(error) + ".");
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
