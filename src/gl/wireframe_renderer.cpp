/*!
 * \brief
 *
 * \author ddubois 
 * \date 20-Nov-16.
 */

#include "wireframe_renderer.h"
#include "../camera.h"
#include "../3rdparty/glm/glm/ext.hpp"

void wireframe_renderer::set_scene(hitable *scene) {
    auto vertices = scene->get_wireframe();
    num_line_segments = (int) (vertices.size() / 2);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, vertices.size() * sizeof(glm::vec3), vertices.data(), 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    load_shader();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *) 3);
    glEnableVertexAttribArray(1);
}

void wireframe_renderer::draw(camera& camera) {
    glBindVertexArray(vao);
    glUseProgram(shader_program);

    upload_view_matrix(camera);

    glDrawArrays(GL_LINES, 0, num_line_segments);
}

void wireframe_renderer::load_shader() {
    const char * vertex_shader_text = "#version 450\n"
            "layout(location = 0) in vec3 position_in;"
            "layout(location = 1) in vec3 color_in;"
            ""
            "layout(location = 0) uniform mat4 view_matrix;"
            ""
            "out vec3 color_frag;"
            ""
            "void main() {"
            "    gl_Position = view_matrix * vec4(position_in, 1);"
            "    color_frag = color_in;"
            "}";

    const char * fragment_shader_text = "#version 450\n"
            "in vec3 color_frag;"
            ""
            "out vec3 color;"
            ""
            "void main() {"
            "    color = vec3(1, 0, 0);"
            "}";

    auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);

    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDetachShader(shader_program, vertex_shader);
    glDeleteShader(vertex_shader);
    glDetachShader(shader_program, fragment_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(shader_program);
}

void wireframe_renderer::upload_view_matrix(camera& cam) {
    glm::mat4 view_matrix = glm::lookAt(cam.get_position(), cam.get_look_target(), cam.get_up());

    glProgramUniformMatrix4fv(shader_program, 0, 1, GL_FALSE, &view_matrix[0][0]);
}
