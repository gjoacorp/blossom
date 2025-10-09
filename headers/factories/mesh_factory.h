#ifndef BLOSSOM_MESH_FACTORY_H
#define BLOSSOM_MESH_FACTORY_H

#include <entt/entt.hpp>
#include "../components/transform_c.h"
#include "../components/mesh_c.h"

namespace blossom::factory
{
  class mesh
  {
    public:
      explicit mesh(entt::registry& registry)
        : registry_(registry)
      {
        entity_    = registry_.create();
        transform_ = &registry_.emplace<transform_c>(entity_);
        mesh_      = &registry_.emplace<mesh_c>(entity_);
      }

      auto with_position(const glm::vec3& position) -> mesh&
      {
        transform_->position = position;
        return *this;
      }

      auto with_scale(const glm::vec3& scale) -> mesh&
      {
        transform_->scale = scale;
        return *this;
      }

      auto with_vertices(const std::vector<glm::vec3>& vertices) -> mesh&
      {
        mesh_->vertices = vertices;
        return *this;
      }

      auto with_indices(const std::vector<GLuint>& indices) -> mesh&
      {
        mesh_->indices = indices;
        return *this;
      }

      auto with_shader_program(const GLuint shader_program) -> mesh&
      {
        mesh_->shader_program = shader_program;
        return *this;
      }

      auto build() -> entt::entity
      {
        return entity_;
      }

    private:
      entt::registry& registry_;
      entt::entity    entity_;
      transform_c*    transform_;
      mesh_c*         mesh_;
  };
}

#endif
