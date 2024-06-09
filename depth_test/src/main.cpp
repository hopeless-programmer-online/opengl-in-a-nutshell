#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <png.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 position;
    glm::vec2 mapping;
};

struct Material
{
    static auto from(const aiScene* scene)
    {
        std::vector<std::shared_ptr<Material>> materials;

        for (size_t i = 0; i < scene->mNumMaterials; ++i)
        {
            const auto material = scene->mMaterials[i];

            aiString path;

            material->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr);

            if (path.length > 0)
            {
                const auto scene_texture = scene->GetEmbeddedTexture(path.C_Str());
                auto file_path = std::string(scene_texture->mFilename.C_Str());

                file_path = "media/" + file_path + ".png";

                png_image image = {};

                image.version = PNG_IMAGE_VERSION;

                if (png_image_begin_read_from_file(&image, file_path.c_str()) == 0) throw std::runtime_error("Failed to load image.");

                image.format = PNG_FORMAT_RGBA;

                std::vector<std::uint8_t> pixels(PNG_IMAGE_SIZE(image));

                if (png_image_finish_read(&image, nullptr, pixels.data(), 0, nullptr) == 0) throw std::runtime_error("Failed to load image.");

                GLuint texture;

                glCreateTextures(GL_TEXTURE_2D, 1, &texture);
                glTextureStorage2D(texture, 1, GL_RGBA8, image.width, image.height);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTextureSubImage2D(texture, 0, 0, 0, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

                materials.push_back(std::make_shared<Material>(texture));
            }
            else
            {
                materials.push_back(nullptr);
            }
        }

        return materials;
    }

    Material(GLuint texture):
        texture(texture)
    {
    }

    GLuint texture;
};

struct Mesh
{
    static auto from(const aiMesh* source, const std::vector<std::shared_ptr<Material>>& materials)
    {
        auto vertices = std::vector<Vertex>(source->mNumVertices);

        for (size_t i = 0; i < source->mNumVertices; ++i) {
            const auto position = source->mVertices[i];
            const auto mapping = source->mTextureCoords[0][i];

            vertices[i] = {
                { position.x, position.y, position.z },
                { mapping.x, 1.0f - mapping.y },
            };
        }

        GLuint vertex_buffer;

        glCreateBuffers(1, &vertex_buffer);
        glNamedBufferStorage(vertex_buffer, sizeof(Vertex) * vertices.size(), vertices.data(), 0);

        auto indices = std::vector<std::uint32_t>(source->mNumFaces * 3);

        for (size_t i = 0; i < source->mNumFaces; ++i)
        {
            indices[i*3 + 0] = source->mFaces[i].mIndices[0];
            indices[i*3 + 1] = source->mFaces[i].mIndices[1];
            indices[i*3 + 2] = source->mFaces[i].mIndices[2];
        }

        GLuint index_buffer;

        glCreateBuffers(1, &index_buffer);
        glNamedBufferStorage(index_buffer, sizeof(decltype(indices)::value_type) * indices.size(), indices.data(), 0);

        GLuint vertex_arrays;

        glCreateVertexArrays(1, &vertex_arrays);
        glVertexArrayVertexBuffer(vertex_arrays, 0, vertex_buffer, 0, sizeof(Vertex));

        glVertexArrayAttribBinding(vertex_arrays, 0, 0);
        glVertexArrayAttribFormat(vertex_arrays, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glEnableVertexArrayAttrib(vertex_arrays, 0);

        glVertexArrayAttribBinding(vertex_arrays, 1, 0);
        glVertexArrayAttribFormat(vertex_arrays, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, mapping));
        glEnableVertexArrayAttrib(vertex_arrays, 1);

        glVertexArrayElementBuffer(vertex_arrays, index_buffer);

        const auto material = source->mMaterialIndex < materials.size() ? materials[source->mMaterialIndex] : nullptr;

        return std::make_shared<Mesh>(vertex_buffer, index_buffer, vertex_arrays, indices.size(), material);
    }
    static auto from(const aiScene* source, const std::vector<std::shared_ptr<Material>>& materials)
    {
        std::vector<std::shared_ptr<Mesh>> meshes;

        for (size_t i = 0; i < source->mNumMeshes; ++i)
        {
            meshes.push_back(Mesh::from(source->mMeshes[i], materials));
        }

        return meshes;
    }

    Mesh(
        GLuint vertex_buffer,
        GLuint index_buffer,
        GLuint vertex_arrays,
        size_t indices_count,
        std::shared_ptr<Material> material
    ):
        vertex_buffer(vertex_buffer),
        index_buffer(index_buffer),
        vertex_arrays(vertex_arrays),
        indices_count(indices_count),
        material(material)
    {
    }

    GLuint vertex_buffer;
    GLuint index_buffer;
    GLuint vertex_arrays;
    size_t indices_count;
    std::shared_ptr<Material> material;
};

struct Node
{
    static auto from(const aiNode* source, const std::vector<std::shared_ptr<Mesh>>& source_meshes, const std::shared_ptr<Node>& parent = nullptr) -> std::shared_ptr<Node>
    {
        std::vector<std::shared_ptr<Mesh>> meshes;

        for (size_t i = 0; i < source->mNumMeshes; ++i)
        {
            meshes.push_back(source_meshes[source->mMeshes[i]]);
        }

        auto m = source->mTransformation;
        auto transformation = glm::transpose(glm::mat4(
            +m.a1, +m.a2, +m.a3, +m.a4,
            +m.b1, +m.b2, +m.b3, +m.b4,
            +m.c1, +m.c2, +m.c3, +m.c4,
            +m.d1, +m.d2, +m.d3, +m.d4
        ));

        if (parent) transformation = parent->transformation * transformation;

        auto node = std::make_shared<Node>(meshes, transformation);

        for (size_t i = 0; i < source->mNumChildren; ++i)
        {
            node->children.push_back(Node::from(source->mChildren[i], source_meshes, node));
        }

        return node;
    }
    static auto from(const aiScene* scene)
    {
        auto materials = Material::from(scene);
        auto meshes = Mesh::from(scene, materials);

        return Node::from(scene->mRootNode, meshes);
    }

    Node(
        const std::vector<std::shared_ptr<Mesh>>& meshes,
        const glm::mat4& transformation
    ):
        meshes(meshes),
        transformation(transformation)
    {
    }

    auto render(GLuint program, const glm::mat4& vp) -> void
    {
        glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, glm::value_ptr(vp * transformation));

        for (const auto &mesh : meshes)
        {
            glActiveTexture(GL_TEXTURE0);

            if (mesh->material)
            {
                glBindTexture(GL_TEXTURE_2D, mesh->material->texture);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            glBindVertexArray(mesh->vertex_arrays);
            glDrawElements(GL_TRIANGLES, mesh->indices_count, GL_UNSIGNED_INT, 0);
        }

        for (const auto &child : children)
        {
            child->render(program, vp);
        }
    }

    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Node>> children;
    glm::mat4                          transformation;
};

std::string VERTEX_SHADER_SOURCE = R"(#version 450
layout (location = 0) uniform mat4 transformation;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inMapping;

layout (location = 0) out vec2 outMapping;

void main() {
    gl_Position = transformation * vec4(inPosition, 1);
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

        const auto window = glfwCreateWindow(1024, 1024, "Depth Test", nullptr, nullptr);

        if (!window) throw std::runtime_error("Window creation failed.");

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) throw std::runtime_error("GLEW initialization failed.");

        Assimp::Importer importer;

        const auto scene = importer.ReadFile("media/room.gltf", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

        auto root = Node::from(scene);

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

        GLuint sampler;

        glCreateSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

        float x = glm::radians(30.0f);
        float y = glm::radians(45.0f);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_UP)) x += glm::radians(1.0f);
            if (glfwGetKey(window, GLFW_KEY_DOWN)) x -= glm::radians(1.0f);
            if (glfwGetKey(window, GLFW_KEY_RIGHT)) y += glm::radians(1.0f);
            if (glfwGetKey(window, GLFW_KEY_LEFT)) y -= glm::radians(1.0f);

            int width, height;

            glfwGetFramebufferSize(window, &width, &height);

            glViewport(0, 0, width, height);
            glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
            glClearDepth(1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glUseProgram(program);

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

            auto rx = glm::transpose(glm::mat3(
                +1.0f, +0.0f,         +0.0f,
                +0.0f, +glm::cos(-x), +glm::sin(-x),
                +0.0f, -glm::sin(-x), +glm::cos(-x)
            ));
            auto ry = glm::transpose(glm::mat3(
                +glm::cos(-y), +0.0f, -glm::sin(-y),
                +0.0f,         +1.0f, +0.0f,
                +glm::sin(-y), +0.0f, +glm::cos(-y)
            ));
            auto t = glm::transpose(glm::mat3x4(
                +1.0f, +0.0f, +0.0f, +0.0f,
                +0.0f, +1.0f, +0.0f, -0.5f,
                +0.0f, +0.0f, +1.0f, -3.0f
            ));

            glm::mat4 view = glm::mat4(t) * glm::mat4(rx) * glm::mat4(ry);

            const auto aspect = static_cast<float>(width) / static_cast<float>(height);
            const auto fov = glm::radians(60.0f);
            const auto z_near = 0.01f;
            const auto z_far = 100.0f;

            glm::mat4 projection = glm::transpose(glm::mat4(
                aspect / glm::cos(fov / 2.0f), 0.0f,                        0.0f,                             0.0f,
                0.0f,                          1.0f / glm::cos(fov / 2.0f), 0.0f,                             0.0f,
                0.0f,                          0.0f,                        -(z_far*z_near)/(z_far - z_near), -(2.0f*z_far*z_near)/(z_far - z_near),
                0.0f,                          0.0f,                        -1.0f,                            0.0f
            ));

            const auto view_projection = projection * view;

            glActiveTexture(GL_TEXTURE0);
            glBindSampler(0, sampler);

            root->render(program, view_projection);

            glFlush();

            glfwSwapBuffers(window);
        }

        // glDeleteSamplers(1, &sampler);
        // glDeleteTextures(1, &texture);
        // glDeleteProgram(program);
        // glDeleteVertexArrays(1, &vertexArrays);
        // glDeleteBuffers(1, &vertexBuffer);
        // glDeleteBuffers(1, &indexBuffer);

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
