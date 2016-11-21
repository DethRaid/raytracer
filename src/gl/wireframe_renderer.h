/*!
 * \brief
 *
 * \author ddubois 
 * \date 20-Nov-16.
 */

#ifndef RAYTRACER_WIREFRAME_RENDERER_H
#define RAYTRACER_WIREFRAME_RENDERER_H

#include <vector>
#include <glad/glad.h>
#include "../3rdparty/glm/glm/glm.hpp"
#include "../hitables/sphere.h"
#include "../hitables/moving_sphere.h"
#include "../hitables/bvh_node.h"

/*!
 * \brief This class is kinda weird. The idea is that you add a bunch of geometry to it, and it'll construct a vertex
 * buffer to render that geometry as wireframe models
 *
 * Probably worth noting that this class is not thread-save in the slightest
 */
class wireframe_renderer {
    /*!
     * \brief Constructs a vertex buffer for wireframe vertices from the given scene and uploads that buffer to the GPU
     */
    void set_scene(hitable* scene);

    void draw();
private:
    GLuint vao;
    GLuint vbo;
};

#endif //RAYTRACER_WIREFRAME_RENDERER_H
