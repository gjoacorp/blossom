#ifndef BLOSSOM_MESH_H
#define BLOSSOM_MESH_H

#include "transform.h"
#include "camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace blossom
{
  class mesh : public transform
  {
    public:
      /// @brief Draws the mesh using the shader program `mesh::shader_program_` and with polygon mode `mesh::polygon_mode_`.
      void draw(const camera* camera) const;

      mesh() = default;
      /**
       * @brief Constructs a mesh using a list of vertices and a shader program.
       * @param vertices is the list of vertices to be passed to the VAO.
       * @param shader_program is the ID of the shader program to use when `mesh::draw()` is called.
       */
      mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program);
      /**
       * @brief Constructs a mesh using a list of vertices, a list of indices, and a shader program.
       * @param vertices is the list of vertices to be passed to the VAO.
       * @param indices is the list of indices to be passed to the EBO.
       * @param shader_program is the ID of the shader program to use when `mesh::draw()` is called.
       */
      mesh(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, GLuint shader_program);
      /// @brief Deletes the vertex array object and buffers referenced in `mesh::vao_`, `mesh::vbo_`, and `mesh::ebo_`.
      ~mesh();

      /** 
       * @brief Sets `mesh::polygon_mode_`.
       * @param polygon_mode must be one of: `GL_LINE`, `GL_POINT`, `GL_FILL`.
       * @throws std::runtime_error if `polygon_mode` is not one of: `GL_LINE`, `GL_POINT`, `GL_FILL`.
       */
      void set_polygon_mode(GLenum polygon_mode);

    protected:
      /// @brief The model-space coordinates of the mesh's vertices.
      std::vector<glm::vec3> vertices_;

      /// @brief Each index refers to a vertex in `mesh::vertices`. Specifying indices can be used to avoid duplicating vertices, which can lead to improved performance when drawing larger meshes.
      std::vector<GLuint> indices_;
      /** 
       * @brief The ID of a program object obtained from [`glCreateProgram()`](httpsb//registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml).
       * 
       * This is intended to be obtained from `shader::program_id`.
       */
      GLuint shader_program_ = 0;
      /// Vertex array object name.
      GLuint vao_            = 0;
      /// Vertex buffer object name.
      GLuint vbo_            = 0;
      /// Element buffer object name.
      GLuint ebo_            = 0;
      /// @brief This is the mode passed to [`glPolygonMode()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml) in `mesh::draw()`.
      GLenum polygon_mode_ = GL_FILL;

      GLuint model_uniform_location_ = 0;
      GLuint view_uniform_location_ = 0;
      GLuint projection_uniform_location_ = 0;

      /**
       * @brief Initialises the mesh's OpenGL resources and sets up vertex array, vertex buffer, and element buffer objects.
       *
       * The IDs for the VAO, VBO, and EBO are stored in `mesh::vao_`, `mesh::vbo_`, and `mesh::ebo_` respectively.
       *
       * @throws std::runtime_error if there is no active OpenGL context when called.
       */
      void init_buffers_();
      void update_uniform_locations_();
  };
}

#endif
