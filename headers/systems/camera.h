#ifndef BLOSSOM_SYSTEM_CAMERA_H
#define BLOSSOM_SYSTEM_CAMERA_H

#include "../components/camera.h"
#include "../components/transform.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>
#include <entt/entt.hpp>

namespace blossom::system
{
  class camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform, component::camera>();
        for (auto [entity, transform, camera] : view.each())
        {
          update_projection_matrix_(camera);
          camera.view_matrix = glm::inverse(transform.matrix);
        }
      }

    private:
      static void update_projection_matrix_(component::camera& camera)
      {
        switch(camera.type)
        {
          case component::camera_type::PERSPECTIVE: 
            {
              const float ASPECT = static_cast<float>(camera.width) / static_cast<float>(camera.height);
              camera.projection_matrix = glm::perspective(glm::radians(camera.fov_y), ASPECT, camera.near, camera.far);
              break;
            }

          case component::camera_type::ORTHOGRAPHIC:
          {
            const float HALF_WIDTH = static_cast<float>(camera.width) / 2.0F;
            const float HALF_HEIGHT = static_cast<float>(camera.height) / 2.0F;

            camera.projection_matrix = glm::ortho(
                -HALF_WIDTH,  HALF_WIDTH, 
                -HALF_HEIGHT, HALF_HEIGHT,
                 camera.near, camera.far
                );
            break;
          }

          default:
            throw std::runtime_error("BLOSSOM_ERROR: Invalid camera type.");
        }
      }
  };
}

#endif 
