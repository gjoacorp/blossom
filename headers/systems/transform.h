#ifndef BLOSSOM_SYSTEM_TRANSFORM_H
#define BLOSSOM_SYSTEM_TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/transform_matrix.h"

namespace blossom::system
{
  class transform
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform, component::transform_matrix>();
        for ( auto [entity, transform, transform_matrix] : view.each() )
        {
          update_transform_matrix_(transform, transform_matrix);
        }
      }

    private:
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
