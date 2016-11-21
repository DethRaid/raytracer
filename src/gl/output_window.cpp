/*!
 * \brief
 *
 * \author ddubois 
 * \date 12-Nov-16.
 */

#include <sstream>
#include <algorithm>
#include <iostream>
#include "../3rdparty/glad/include/glad/glad.h"
#include "output_window.h"
#include "../3rdparty/glm/glm/glm.hpp"

std::string translate_debug_source(GLenum source) {
    switch(source) {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "window system";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "shader compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "third party";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "application";
        case GL_DEBUG_SOURCE_OTHER:
            return "other";
        default:
            return "something else somehow";
    }
}

std::string translate_debug_type(GLenum type) {
    switch(type) {
        case GL_DEBUG_TYPE_ERROR:
            return "error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "some behavior marked deprecated has been used";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "something has invoked undefined behavior";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "some functionality the user relies upon is not portable";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "code has triggered possible performance issues";
        case GL_DEBUG_TYPE_MARKER:
            return "command stream annotation";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return "group pushing";
        case GL_DEBUG_TYPE_POP_GROUP:
            return "group popping";
        case GL_DEBUG_TYPE_OTHER:
            return "other";
        default:
            return "something else somwhow";
    }
}

void debug_logger(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                  const void *user_param) {
    std::string source_name = translate_debug_source(source);
    std::string type_name = translate_debug_type(type);

    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << id << " [HIGH   ] - Message from " << source_name << " of type " << type_name << ": "
                       << message << "\n";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << id << " [MEDIUM ] - Message from " << source_name << " of type " << type_name << ": " << message << "\n";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            std::cout << id << " [LOW    ] - Message from " << source_name << " of type " << type_name << ": "
                       << message << "\n";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << id << " [NOTIF  ] - Message from " << source_name << " of type " << type_name << ": "
                       << message << "\n";
            break;

        default:
            std::cout << id << " [DEFAULT] - Message from " << source_name << " of type " << type_name << ": " << message << "\n";
    }
}

output_window::output_window(unsigned width, unsigned height) {
    create_window(width, height);
    create_fullscreen_quad();
    create_shader_program();
}

void output_window::create_window(unsigned int width, unsigned int height) {
    if(!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfw_window = glfwCreateWindow(width, height, "Raytracer output", NULL, NULL);
    if(!glfw_window) {
        glfwTerminate();
        throw std::runtime_error("Could not create a window");
    }

    glfwMakeContextCurrent(glfw_window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Could not initialize the OpenGL context");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_logger, NULL);

    glm::ivec2 window_size;
    glfwGetFramebufferSize(glfw_window, &window_size.x, &window_size.y);
    glViewport(0, 0, window_size.x, window_size.y);
}

output_window::~output_window() {
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

void output_window::create_fullscreen_quad() {
    // The vertex data
    std::vector<float> vertices = {
            -1, -1,
            -1,  1,
             1,  1,
             1, -1,
    };

    std::vector<unsigned short> indices = {
            1, 0, 3,
            2, 1, 3
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
}

void output_window::create_shader_program() {
    static const char * vertex_source = "#version 450\n"
            ""
            "layout(location = 0) in vec2 position;"
            ""
            "out vec2 uv;"
            ""
            "void main() {"
            "    gl_Position = vec4(position, 0, 1);"
            "    uv = position * 0.5 + 0.5;"
            "}";

    static const char * fragment_source = "#version 450\n"
            ""
            "in vec2 uv;"
            ""
            "layout(binding = 0) uniform sampler2D image;"
            ""
            "layout(location = 0) out vec3 color;"
            ""
            "void main() {"
            "    color = texture(image, uv, 0).rgb;"
            "}";

    auto vertex_shader_name = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_name, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader_name);

    auto fragment_shader_name = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_name, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader_name);

    check_for_shader_errors(vertex_shader_name);
    check_for_shader_errors(fragment_shader_name);

    auto program = glCreateProgram();
    glAttachShader(program, vertex_shader_name);
    glAttachShader(program, fragment_shader_name);

    glLinkProgram(program);

    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);

    if(is_linked == GL_FALSE) {
        GLint log_size = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);

        std::vector<GLchar> error_log((unsigned long long int) log_size);
        glGetProgramInfoLog(program, log_size, &log_size, error_log.data());

        if(log_size > 0) {
            glDeleteProgram(program);

            std::stringstream sb;
            sb << "Error linking program " << program << ":\n" << error_log.data();
            throw std::runtime_error(sb.str());
        }
    }

    glDetachShader(program, fragment_shader_name);
    glDeleteShader(fragment_shader_name);

    glDetachShader(program, vertex_shader_name);
    glDeleteShader(vertex_shader_name);

    glUseProgram(program);
}

void output_window::check_for_shader_errors(GLuint shader_to_check) const {
    GLint success = 0;

    glGetShaderiv(shader_to_check, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE) {
        GLint log_size = 0;
        glGetShaderiv(shader_to_check, GL_INFO_LOG_LENGTH, &log_size);

        std::vector<GLchar> error_log((unsigned long long int) log_size);
        glGetShaderInfoLog(shader_to_check, log_size, &log_size, &error_log[0]);

        if(log_size > 0) {
            glDeleteShader(shader_to_check);
            throw std::runtime_error(error_log.data());
        }
    }
}

void
output_window::set_texture(std::vector<glm::vec3> &texture_data, unsigned width, unsigned height) {
    GLuint texture = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, 1, GL_RGB8, width, height);
    glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, texture_data.data());

    glBindTextureUnit(0, texture);

    while(!glfwWindowShouldClose(glfw_window)) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        glfwPollEvents();
        glfwSwapBuffers(glfw_window);
    }
}
