#ifndef BLOSSOM_SYSTEM_PERSPECTIVE_CAMERA_H
#define BLOSSOM_SYSTEM_PERSPECTIVE_CAMERA_H

#include "../components/perspective_camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "../components/transform_matrix.h"
#include "../components/view_projection_matrix.h"
#include <entt/entt.hpp>

namespace blossom::system
{
  class perspective_camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform_matrix, component::view_projection_matrix, component::perspective_camera>();
        for (auto [entity, transform_matrix, vp_matrix, camera] : view.each())
        {
          auto view_projection_matrix = calculate_projection_matrix_(camera);
          view_projection_matrix *= glm::inverse(transform_matrix.matrix);
          vp_matrix.matrix = view_projection_matrix;
        }
      }

    private:
      static auto calculate_projection_matrix_(const component::perspective_camera& camera) -> glm::mat4
      {
        const float ASPECT = static_cast<float>(camera.width) / static_cast<float>(camera.height);
        return glm::perspective(glm::radians(camera.fov_y), ASPECT, camera.near, camera.far);
      }
  };
}

#endif 
