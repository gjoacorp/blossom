#ifndef BLOSSOM_TRANSFORM_SYSTEM_H
#define BLOSSOM_TRANSFORM_SYSTEM_H

#include <glm/gtc/matrix_transform.hpp>
#include <entt/entt.hpp>
#include "../components/transform_c.h"

namespace blossom
{
  class transform_system
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<transform_c>();
        for ( auto [entity, transform] : view.each() )
        {
          update_transform_matrix_(transform);
        }
      }

    private:
      static void update_transform_matrix_(transform_c& transform)
      {
        auto transform_matrix = glm::mat4(1.0F);

        transform_matrix = glm::translate(transform_matrix, transform.position);
        transform_matrix = glm::rotate(transform_matrix, glm::radians(transform.rotation.x), glm::vec3(1.0F, 0.0F, 0.0F));
        transform_matrix = glm::rotate(transform_matrix, glm::radians(transform.rotation.y), glm::vec3(0.0F, 1.0F, 0.0F));
        transform_matrix = glm::rotate(transform_matrix, glm::radians(transform.rotation.z), glm::vec3(0.0F, 0.0F, 1.0F));
        transform_matrix = glm::scale(transform_matrix, transform.scale);

        transform.matrix = transform_matrix;
      }

  };
}

#endif 
