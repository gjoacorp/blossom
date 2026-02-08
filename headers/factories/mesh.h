#ifndef BLOSSOM_FACTORY_MESH_H
#define BLOSSOM_FACTORY_MESH_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/mesh.h"

namespace blossom::factory
{
  class mesh
  {
    public:
      explicit mesh(entt::registry& registry)
        : registry_(registry)
      {
        entity_    = registry_.create();
        registry_.emplace<component::mesh>(entity_);
        registry_.emplace<component::transform>(entity_);
      }

      auto with_position(const glm::vec3& position) -> mesh&
      {
        registry_.get<component::transform>(entity_).position = position;
        return *this;
      }

      auto with_scale(const glm::vec3& scale) -> mesh&
      {
        registry_.get<component::transform>(entity_).scale = scale;
        return *this;
      }

      auto with_vertices(std::vector<glm::vec3> vertices) -> mesh&
      {
        vertices_ = std::move(vertices);
        return *this;
      }

      auto with_indices(std::vector<GLuint> indices) -> mesh&
      {
        indices_ = std::move(indices);
        return *this;
      }

      auto with_shader_program(const GLuint shader_program) -> mesh&
      {
        registry_.get<component::mesh>(entity_).shader_program = shader_program;
        return *this;
      }

      auto with_primitive_type(const GLenum primitive_type) -> mesh&
      {
        registry_.get<component::mesh>(entity_).primitive_type = primitive_type;
        return *this;
      }

      auto with_polygon_mode(const GLenum polygon_mode) -> mesh&
      {
        registry_.get<component::mesh>(entity_).polygon_mode = polygon_mode;
        return *this;
      }

      auto clean_up() -> entt::entity
      {
        vertices_.clear(); indices_.clear();
        vertices_.shrink_to_fit(); indices_.shrink_to_fit();

        return entity_;
      }

      auto build() -> entt::entity
      {
        auto& mesh = registry_.get<component::mesh>(entity_);

        mesh.vertex_count = static_cast<GLsizei>(vertices_.size());
        mesh.index_count = static_cast<GLsizei>(indices_.size());

        init_uniform_locations_();
        init_buffers_();

        return entity_;
      }

    private:
      entt::registry&        registry_;
      entt::entity           entity_;

      std::vector<glm::vec3> vertices_;
      std::vector<GLuint> indices_;

      void init_uniform_locations_()
      {
        auto& mesh = registry_.get<component::mesh>(entity_);

        mesh.model_uniform_location      = glGetUniformLocation(mesh.shader_program, "model");
        mesh.view_uniform_location       = glGetUniformLocation(mesh.shader_program, "view");
        mesh.projection_uniform_location = glGetUniformLocation(mesh.shader_program, "projection");
      }

      void init_buffers_()
      {
        auto& mesh = registry_.get<component::mesh>(entity_);

        glCreateVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glCreateBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glNamedBufferStorage(
            mesh.vbo, 
            static_cast<GLsizeiptr>( vertices_.size() * sizeof(glm::vec3) ), 
            vertices_.data(), 
            0);

        if (indices_.size() > 0)
        {
          glCreateBuffers(1, &mesh.ebo);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
          glNamedBufferStorage(
              mesh.ebo, 
              static_cast<GLsizeiptr>( indices_.size() * sizeof(GLuint) ), 
              indices_.data(), 
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
