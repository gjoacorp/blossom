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

      auto with_vertices(const std::vector<glm::vec3>& vertices) -> mesh&
      {
        registry_.get<component::mesh>(entity_).vertices = vertices;
        return *this;
      }

      auto with_indices(const std::vector<GLuint>& indices) -> mesh&
      {
        registry_.get<component::mesh>(entity_).indices = indices;
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

      auto build() -> entt::entity
      {
        return entity_;
      }

    private:
      entt::registry&       registry_;
      entt::entity          entity_;
  };
}

#endif
