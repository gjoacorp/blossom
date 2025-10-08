#ifndef BLOSSOM_MESH_SYSTEM_H
#define BLOSSOM_MESH_SYSTEM_H

#include <entt/entt.hpp>
#include "../components/mesh_c.h"

namespace blossom
{
  class mesh_system
  {
    public:
      static void init(entt::registry& registry)
      {
        auto view = registry.view<mesh_c>();
        for ( auto [entity, mesh] : view.each() )
        {
          init_uniform_locations_(mesh);
          init_buffers_(mesh);
        }
      }

      static void update(entt::registry& registry)
      {
        auto view = registry.view<mesh_c>();
        for ( auto [entity, mesh] : view.each() )
        {
          init_uniform_locations_(mesh);
          init_buffers_(mesh);
        }
      }

    private:
      static void init_uniform_locations_(mesh_c& mesh)
      {
        mesh.model_uniform_location      = glGetUniformLocation(mesh.shader_program, "model");
        mesh.view_uniform_location       = glGetUniformLocation(mesh.shader_program, "view");
        mesh.projection_uniform_location = glGetUniformLocation(mesh.shader_program, "projection");
      }

      static void init_buffers_(mesh_c& mesh)
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
