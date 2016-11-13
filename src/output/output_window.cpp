/*!
 * \brief
 *
 * \author ddubois 
 * \date 12-Nov-16.
 */

#include <sstream>
#include "../3rdparty/glfw/deps/glad/glad.h"
#include "output_window.h"

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
}

output_window::~output_window() {
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

void output_window::create_fullscreen_quad() {
    // The vertex data
    std::vector<float> vertices = {
            -1, -1,  0, 0,
            -1,  1,  0, 1,
             1,  1,  1, 1,
             1, -1,  1, 0
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
}

void output_window::create_shader_program() {
    static const char * vertex_source = "#version 450\n"
            ""
            "layout(location = 0) in vec2 position;"
            "layout(location = 1) in vec2 uv_in;"
            ""
            "out vec2 uv;"
            ""
            "void main() {"
            "    gl_Position = vec4(position, 0, 1);"
            "    uv = uv_in;"
            "}";

    static const char * fragment_source = "#version 450\n"
            ""
            "in vec2 uv;"
            ""
            "layout(location = 0) uniform sampler2D image;"
            ""
            "out vec3 color;"
            ""
            "void main() {"
            "    color = texture(image, uv).rgb;"
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
