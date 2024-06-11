#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec2 position;
    glm::vec2 mapping;
};

std::string VERTEX_SHADER_SOURCE = R"(#version 450
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inMapping;

layout (location = 0) out vec2 outMapping;

void main() {
    gl_Position = vec4(inPosition, 0, 1);
    outMapping = inMapping;
}
)";
const char* VERTEX_SHADER_SOURCES[] = { VERTEX_SHADER_SOURCE.c_str() };
const GLint VERTEX_SHADER_LENGTHS[] = { static_cast<GLint>(VERTEX_SHADER_SOURCE.length()) };

std::string FRAGMENT_SHADER_SOURCE = R"(#version 450
layout (binding = 0) uniform sampler2D textureColor;

layout (location = 0) in vec2 inMapping;

layout (location = 0) out vec4 outColor;

void main() {
    // outColor = vec4(inMapping, 0, 1);
    outColor = texture(textureColor, inMapping);
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

        const auto window = glfwCreateWindow(800, 600, "Texture", nullptr, nullptr);

        if (!window) throw std::runtime_error("Window creation failed.");

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) throw std::runtime_error("GLEW initialization failed.");

        const auto vertices = std::vector<Vertex>{
            { { -0.5f, -0.5f }, { 0.0f, 0.0f } },
            { { +0.5f, -0.5f }, { 1.0f, 0.0f } },
            { { -0.5f, +0.5f }, { 0.0f, 1.0f } },
            { { +0.5f, +0.5f }, { 1.0f, 1.0f } },
        };

        GLuint vertexBuffer;

        glCreateBuffers(1, &vertexBuffer);
        glNamedBufferStorage(vertexBuffer, sizeof(Vertex) * vertices.size(), vertices.data(), 0);

        const auto indices = std::vector<std::uint32_t>{
            0, 1, 2,
            1, 3, 2,
        };

        GLuint indexBuffer;

        glCreateBuffers(1, &indexBuffer);
        glNamedBufferStorage(indexBuffer, sizeof(decltype(indices)::value_type) * indices.size(), indices.data(), 0);

        GLuint vertexArrays;

        glCreateVertexArrays(1, &vertexArrays);
        glVertexArrayVertexBuffer(vertexArrays, 0, vertexBuffer, 0, sizeof(Vertex));

        glVertexArrayAttribBinding(vertexArrays, 0, 0);
        glVertexArrayAttribFormat(vertexArrays, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glEnableVertexArrayAttrib(vertexArrays, 0);

        glVertexArrayAttribBinding(vertexArrays, 1, 0);
        glVertexArrayAttribFormat(vertexArrays, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, mapping));
        glEnableVertexArrayAttrib(vertexArrays, 1);

        glVertexArrayElementBuffer(vertexArrays, indexBuffer);

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

        std::vector<std::uint8_t> pixels = {
            255, 0, 0,
            0, 255, 0,
            0, 0, 255,

            0, 255, 255,
            255, 0, 255,
            255, 255, 0,

            0, 0, 0,
            127, 127, 127,
            255, 255, 255,
        };

        GLuint texture;

        glCreateTextures(GL_TEXTURE_2D, 1, &texture);
        glTextureStorage2D(texture, 1, GL_RGB8, 3, 3);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTextureSubImage2D(texture, 0, 0, 0, 3, 3, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

        GLuint sampler;

        glCreateSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

            glBindTextureUnit(0, texture);
            glBindSampler(0, sampler);

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glFlush();

            glfwSwapBuffers(window);
        }

        glDeleteSamplers(1, &sampler);
        glDeleteTextures(1, &texture);
        glDeleteProgram(program);
        glDeleteVertexArrays(1, &vertexArrays);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &vertexBuffer);

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
