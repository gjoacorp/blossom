#ifndef BLOSSOM_MESH_H
#define BLOSSOM_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

namespace blossom
{
  class mesh
  {
    public:
      /// @brief Draws the mesh using the shader program `mesh::shader_program_` and with polygon mode `mesh::polygon_mode_`.
      void draw() const;

      mesh() = default;
      /**
       * @brief Constructs a mesh using a list of vertices and a shader program.
       */
      mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program);
      /**
       * @brief Constructs a mesh using a list of vertices, a list of indices, and a shader program.
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
      GLuint shader_program_;
      GLuint vao_ = 0;
      GLuint vbo_ = 0;
      GLuint ebo_ = 0;
      /// @brief This is the mode passed to [`glPolygonMode()`](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml) in `mesh::draw()`.
      GLenum polygon_mode_ = GL_FILL;

      /**
       * @brief Initialises the mesh's OpenGL resources and sets up vertex array, vertex buffer, and element buffer objects.
       *
       * The IDs for the VAO, VBO, and EBO are stored in `mesh::vao_`, `mesh::vbo_`, and `mesh::ebo_` respectively.
       *
       * @throws std::runtime_error if there is no active OpenGL context when called.
       */
      void init_();
  };
}

#endif
