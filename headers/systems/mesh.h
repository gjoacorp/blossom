#ifndef BLOSSOM_SYSTEM_MESH_H
#define BLOSSOM_SYSTEM_MESH_H

#include <entt/entt.hpp>
#include "../components/mesh.h"

namespace blossom::system
{
  class mesh
  {
    public:
      static void init(entt::registry& registry)
      {
        auto view = registry.view<component::mesh>();
        for ( auto [entity, mesh] : view.each() )
        {
          init_uniform_locations_(mesh);
          init_buffers_(mesh);
        }
      }

      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::mesh>();
        for ( auto [entity, mesh] : view.each() )
        {
          init_uniform_locations_(mesh);
          init_buffers_(mesh);
        }
      }

    private:
      static void init_uniform_locations_(component::mesh& mesh)
      {
        mesh.model_uniform_location      = glGetUniformLocation(mesh.shader_program, "model");
        mesh.view_uniform_location       = glGetUniformLocation(mesh.shader_program, "view");
        mesh.projection_uniform_location = glGetUniformLocation(mesh.shader_program, "projection");
      }

      static void init_buffers_(component::mesh& mesh)
      {
        glCreateVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glCreateBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glNamedBufferStorage(
            mesh.vbo, 
            static_cast<GLsizeiptr>( mesh.vertices.size() * sizeof(glm::vec3) ), 
            mesh.vertices.data(), 
            0);

        if (mesh.indices.size() > 0)
        {
          glCreateBuffers(1, &mesh.ebo);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
          glNamedBufferStorage(
              mesh.ebo, 
              static_cast<GLsizeiptr>( mesh.indices.size() * sizeof(GLuint) ), 
              mesh.indices.data(), 
              0);
        }

        glVertexAttribPointer(
            0, 
            3, 
            GL_FLOAT, 
            GL_FALSE, 
            sizeof(glm::vec3), 
            nullptr );

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
      }
  };
}

#endif
