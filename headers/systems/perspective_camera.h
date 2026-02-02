#ifndef BLOSSOM_SYSTEM_PERSPECTIVE_CAMERA_H
#define BLOSSOM_SYSTEM_PERSPECTIVE_CAMERA_H

#include "../components/perspective_camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "../components/transform.h"
#include <entt/entt.hpp>

namespace blossom::system
{
  class perspective_camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform, component::perspective_camera>();
        for (auto [entity, transform, camera] : view.each())
        {
          update_projection_matrix_(camera);
          camera.view_matrix = glm::inverse(transform.matrix);
        }
      }

    private:
      static void update_projection_matrix_(component::perspective_camera& camera)
      {
        const float ASPECT = static_cast<float>(camera.width) / static_cast<float>(camera.height);
        camera.projection_matrix = glm::perspective(glm::radians(camera.fov_y), ASPECT, camera.near, camera.far);
      }
  };
}

#endif 
