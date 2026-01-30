#ifndef BLOSSOM_SYSTEM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_SYSTEM_ORTHOGRAPHIC_CAMERA_H

#include "../components/orthographic_camera.h"
#include "../components/transform.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <entt/entt.hpp>

namespace blossom::system
{
  class orthographic_camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform, component::orthographic_camera>();
        for (auto [entity, transform, camera] : view.each())
        {
          update_projection_matrix_(camera);
          camera.view_matrix = glm::inverse(transform.matrix);
        }
      }

    private:
      static void update_projection_matrix_(component::orthographic_camera& camera)
      {
        const float HALF_WIDTH = static_cast<float>(camera.width) / 2.0F;
        const float HALF_HEIGHT = static_cast<float>(camera.height) / 2.0F;

        camera.projection_matrix = glm::ortho(
            -HALF_WIDTH, HALF_WIDTH, 
            -HALF_HEIGHT, HALF_HEIGHT,
            camera.near, camera.far
            );
      }
  };
}

#endif 
