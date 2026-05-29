#ifndef BLOSSOM_FACTORY_MESH_H
#define BLOSSOM_FACTORY_MESH_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/transform_matrix.h"
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
        registry_.emplace<component::transform_matrix>(entity_);
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
        points_ = std::move(vertices);
        return *this;
      }

      auto with_uv(std::vector<glm::vec2> uv) -> mesh&
      {
        uv_ = std::move(uv);
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

        // If uv_ is empty, this means that .with_uv() wasn't called.
        // Hence, we fill the uv_ container with (0, 0) values.
        if (uv_.empty())
        {
          uv_.assign(points_.size(), glm::vec2());
        }

        // vertices_ is organised into 4-byte blocks as shown below:
        //
        // | X | Y | Z | U | V |
        //
        // If uv_ is never supplied ( i.e. via .with_uv() ) then U and V are zero.
        for (size_t i = 0; i < points_.size(); i++)
        {
          vertices_.push_back(points_[i].x);
          vertices_.push_back(points_[i].y);
          vertices_.push_back(points_[i].z);
          vertices_.push_back(uv_.at(i).x);
          vertices_.push_back(uv_.at(i).y);
        }

        mesh.vertex_count = static_cast<GLsizei>(vertices_.size());
        mesh.index_count = static_cast<GLsizei>(indices_.size());

        init_uniform_locations_();
        init_buffers_();

        return entity_;
      }

    private:
      entt::registry&        registry_;
      entt::entity           entity_;

      std::vector<glm::vec3> points_; // (x, y, z) coordinates representing the mesh's geometric vertices' positions ( in local-space ).
      std::vector<glm::vec2> uv_;     // texture coordinates

      std::vector<float> vertices_;   // this is an unpacked container obtained by continuously merging points and texture coordinates
      std::vector<GLuint> indices_;

      void init_uniform_locations_()
      {
        auto& mesh = registry_.get<component::mesh>(entity_);
        mesh.mvp_uniform_location = glGetUniformLocation(mesh.shader_program, "mvp_matrix");
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
            static_cast<GLsizeiptr>(vertices_.size() * sizeof(float)),
            vertices_.data(), 
            0);

        // If indices are supplied, we store them in an EBO.
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
          sizeof(glm::vec3) + sizeof(glm::vec2),
          nullptr
        );
        glEnableVertexAttribArray(0);

        //  Vertex UV
        glVertexAttribPointer(
          1,
          2,
          GL_FLOAT,
          GL_FALSE,
          sizeof(glm::vec3) + sizeof(glm::vec2),
          reinterpret_cast<void*>(sizeof(glm::vec3))
        );
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
      }
  };
}

#endif
