#ifndef BLOSSOM_SYSTEM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_SYSTEM_ORTHOGRAPHIC_CAMERA_H

#include "../components/orthographic_camera.h"
#include "../components/transform_matrix.h"
#include "../components/view_projection_matrix.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <entt/entt.hpp>

namespace blossom::system
{
  class orthographic_camera
  {
    public:
      static void update(entt::registry& registry)
      {
        auto view = registry.view<component::transform_matrix, component::view_projection_matrix, component::orthographic_camera, component::tag::dirty>();
        for (auto [entity, transform_matrix, vp_matrix, camera] : view.each())
        {
          auto view_projection_matrix = calculate_projection_matrix_(camera);
          view_projection_matrix *= glm::inverse(transform_matrix.matrix);
          vp_matrix.matrix = view_projection_matrix;

          registry.remove<component::tag::dirty>(entity);
        }
      }

    private:
      static auto calculate_projection_matrix_(const component::orthographic_camera& camera) -> glm::mat4
      {
        const float HALF_WIDTH = static_cast<float>(camera.width) / 2.0F;
        const float HALF_HEIGHT = static_cast<float>(camera.height) / 2.0F;

        return glm::ortho(
            -HALF_WIDTH, HALF_WIDTH, 
            -HALF_HEIGHT, HALF_HEIGHT,
            camera.near, camera.far
            );
      }
  };
}

#endif 
