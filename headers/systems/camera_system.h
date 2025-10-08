#ifndef BLOSSOM_CAMERA_SYSTEM_H
#define BLOSSOM_CAMERA_SYSTEM_H

#include "../components/camera_c.h"
#include "../components/transform_c.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>
#include <entt/entt.hpp>

namespace blossom
{
  class camera_system
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<transform_c, camera_c>();
        for (auto [entity, transform, camera] : view.each())
        {
          update_projection_matrix_(camera);
          camera.view_matrix = glm::inverse(transform.matrix);
        }
      }

    private:
      static void update_projection_matrix_(camera_c& camera)
      {
        switch(camera.type)
        {
          case camera_type::PERSPECTIVE: 
            {
              const float ASPECT = static_cast<float>(camera.width) / static_cast<float>(camera.height);
              camera.projection_matrix = glm::perspective(glm::radians(camera.fov_y), ASPECT, camera.near, camera.far);
              break;
            }

          case camera_type::ORTHOGRAPHIC:
            camera.projection_matrix = glm::ortho(
                0.0F, 
                static_cast<float>(camera.width), 
                0.0F, static_cast<float>(camera.height), 
                camera.near, 
                camera.far
                );
            break;

          default:
            throw std::runtime_error("BLOSSOM_ERROR: Invalid camera type.");
        }
      }
  };
}

#endif 
