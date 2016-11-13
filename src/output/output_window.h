/*!
 * \brief
 *
 * \author ddubois 
 * \date 12-Nov-16.
 */

#ifndef RAYTRACER_WINDOW_H
#define RAYTRACER_WINDOW_H

#include <memory>
#include <vector>
#include "../3rdparty/glfw/include/GLFW/glfw3.h"
#include "../3rdparty/glm/glm/vec3.hpp"

/*!
 * \brief Represents a window, which is kinda useful because I want to show the output of the raytracer to the world
 */
class output_window {
public:
    output_window(unsigned width, unsigned height);
    virtual ~output_window();

    /*!
     * \brief Sets the texture that this window should display to the provided texture
     *
     * This method causes the window to re-draw. It also creates a new texture
     *
     * \param texture_data The raw pixels of the image
     * \param width The width of the image
     * \param height The height of the image
     * \param comp The number of components in the image
     */
    void set_texture(std::vector<glm::vec3> &texture_data, unsigned width, unsigned height, unsigned char comp);

private:
    GLFWwindow* glfw_window;

    void create_window(unsigned int width, unsigned int height);

    void create_fullscreen_quad();

    void create_shader_program();

    void check_for_shader_errors(GLuint shader_to_check) const;
};


#endif //RAYTRACER_WINDOW_H
