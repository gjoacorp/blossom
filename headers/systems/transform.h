#ifndef BLOSSOM_SYSTEM_TRANSFORM_H
#define BLOSSOM_SYSTEM_TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include "../systems/base_system.h"
#include "../components/transform.h"
#include "../components/transform_matrix.h"
#include "../components/tags/dirty.h"

#include "../components/orthographic_camera.h"
#include "../components/perspective_camera.h"

namespace blossom::system
{
  class transform : public base_system<transform>
  {
    friend class base_system<transform>;

    private:
    static void init_impl_(entt::registry& registry)
    {
      registry.on_construct<component::transform>().connect<&on_construct_>();
    }

    static void update_impl_(entt::registry& registry)
    {
      auto view = registry.view<component::transform, component::transform_matrix, component::tag::dirty>();
      for ( auto [entity, transform, transform_matrix] : view.each() )
      {
        update_transform_matrix_(transform, transform_matrix);

        auto* ortho_camera = registry.try_get<component::orthographic_camera>(entity);
        auto* persp_camera = registry.try_get<component::perspective_camera>(entity);

        if (!ortho_camera && !persp_camera)
        {
          registry.remove<component::tag::dirty>(entity);
        }
      }
    }

    static void on_construct_impl_(entt::registry& registry, entt::entity entity)
    {
      registry.emplace_or_replace<component::tag::dirty>(entity);
      registry.emplace_or_replace<component::transform_matrix>(entity);
    }

    static void update_transform_matrix_(const component::transform& transform, component::transform_matrix& transform_matrix)
    {
      auto local_to_world = glm::mat4(1.0F);

      local_to_world = glm::translate(local_to_world, transform.position);
      local_to_world = glm::rotate(local_to_world, glm::radians(transform.rotation.x), glm::vec3(1.0F, 0.0F, 0.0F));
      local_to_world = glm::rotate(local_to_world, glm::radians(transform.rotation.y), glm::vec3(0.0F, 1.0F, 0.0F));
      local_to_world = glm::rotate(local_to_world, glm::radians(transform.rotation.z), glm::vec3(0.0F, 0.0F, 1.0F));
      local_to_world = glm::scale(local_to_world, transform.scale);

      transform_matrix.matrix = local_to_world;
    }
  };
}

#endif 
