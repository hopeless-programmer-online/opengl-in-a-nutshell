#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


std::string VERTEX_SHADER_SOURCE = R"(#version 450

layout (binding = 0) uniform Coordinates {
    float coordinates[6];
};

void main() {
    gl_Position = vec4(
        coordinates[gl_VertexID*2 + 0],
        coordinates[gl_VertexID*2 + 1],
        0,
        1
    );
}
)";
const char* VERTEX_SHADER_SOURCES[] = { VERTEX_SHADER_SOURCE.c_str() };
const GLint VERTEX_SHADER_LENGTHS[] = { static_cast<GLint>(VERTEX_SHADER_SOURCE.length()) };

std::string FRAGMENT_SHADER_SOURCE = R"(#version 450
layout (location = 0) out vec4 color;

void main() {
    color = vec4(0, 0.5, 1, 1);
}
)";
const char* FRAGMENT_SHADER_SOURCES[] = { FRAGMENT_SHADER_SOURCE.c_str() };
const GLint FRAGMENT_SHADER_LENGTHS[] = { static_cast<GLint>(FRAGMENT_SHADER_SOURCE.length()) };


int main() {
    try {
        if (!glfwInit()) throw std::runtime_error("GLFW initialization failed.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const auto window = glfwCreateWindow(800, 600, "Uniform buffer triangle", nullptr, nullptr);

        if (!window) throw std::runtime_error("Window creation failed.");

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) throw std::runtime_error("GLEW initialization failed.");

        GLuint vertexArrays;

        glCreateVertexArrays(1, &vertexArrays);

        const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, VERTEX_SHADER_SOURCES, VERTEX_SHADER_LENGTHS);
        glCompileShader(vertexShader);

        GLint vertexShaderCompileStatus;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);

        if (vertexShaderCompileStatus != GL_TRUE) {
            GLint size = 0;

            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &size);

            std::string log;

            log.resize(size);
            glGetShaderInfoLog(vertexShader, size, &size, log.data());

            throw std::runtime_error(log);
        }

        const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, FRAGMENT_SHADER_SOURCES, FRAGMENT_SHADER_LENGTHS);
        glCompileShader(fragmentShader);

        GLint fragmentShaderCompileStatus;

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);

        if (fragmentShaderCompileStatus != GL_TRUE) {
            GLint size = 0;

            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &size);

            std::string log;

            log.resize(size);
            glGetShaderInfoLog(fragmentShader, size, &size, log.data());

            throw std::runtime_error(log);
        }

        const auto program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        GLint linkStatus;

        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (linkStatus != GL_TRUE) {
            GLint size = 0;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

            std::string log;

            log.resize(size);
            glGetProgramInfoLog(program, size, &size, log.data());

            throw std::runtime_error(log);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float coordinates1[] = {
            -0.5f, -0.5f,
            +0.4f, -0.5f,
            -0.5f, +0.5f,
        };

        GLuint vertexBuffer1;

        glCreateBuffers(1, &vertexBuffer1);
        glNamedBufferStorage(vertexBuffer1, sizeof(coordinates1), coordinates1, 0);

        float coordinates2[] = {
            +0.5f, -0.5f,
            +0.5f, +0.5f,
            -0.4f, +0.5f,
        };

        GLuint vertexBuffer2;

        glCreateBuffers(1, &vertexBuffer2);
        glNamedBufferStorage(vertexBuffer2, sizeof(coordinates2), coordinates2, 0);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            int width, height;

            glfwGetFramebufferSize(window, &width, &height);

            glViewport(0, 0, width, height);
            glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(vertexArrays);
            glUseProgram(program);
            glValidateProgram(program);

            GLint validateStatus;

            glGetProgramiv(program, GL_VALIDATE_STATUS, &validateStatus);

            if (validateStatus != GL_TRUE) {
                GLint size = 0;

                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);

                std::string log;

                log.resize(size);
                glGetProgramInfoLog(program, size, &size, log.data());

                throw std::runtime_error(log);
            }

            glBindBufferBase(GL_UNIFORM_BUFFER, 0, vertexBuffer1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindBufferBase(GL_UNIFORM_BUFFER, 0, vertexBuffer2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glFlush();

            glfwSwapBuffers(window);
        }

        glDeleteBuffers(1, &vertexBuffer1);
        glDeleteBuffers(1, &vertexBuffer2);
        glDeleteProgram(program);
        glDeleteVertexArrays(1, &vertexArrays);

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
