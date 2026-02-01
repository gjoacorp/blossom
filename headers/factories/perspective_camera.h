#ifndef BLOSSOM_FACTORY_PERSPECTIVE_CAMERA_H
#define BLOSSOM_FACTORY_PERSPECTIVE_CAMERA_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/perspective_camera.h"
#include "../components/tags/active_camera.h"

namespace blossom::factory
{
  class perspective_camera
  {
    public:
      explicit perspective_camera(entt::registry& registry) 
        : registry_(registry)
      {
        entity_    =  registry_.create();
        camera_    = &registry_.emplace<component::perspective_camera>(entity_);
        transform_ = &registry_.emplace<component::transform>(entity_);
      }

      auto with_width(const uint16_t width) -> perspective_camera&
      {
        camera_->width = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> perspective_camera&
      {
        camera_->height = height;
        return *this;
      }

      auto with_fov_y(float fov_y) -> perspective_camera&
      {
        camera_->fov_y = fov_y;
        return *this;
      }

      auto with_position(const glm::vec3& position) -> perspective_camera&
      {
        transform_->position = position;
        return *this;
      }

      auto with_rotation(const glm::vec3& rotation) -> perspective_camera&
      {
        transform_->rotation = rotation;
        return *this;
      }

      auto make_active() -> perspective_camera&
      {
        auto view = registry_.view<component::tag::active_camera>();
        registry_.remove<component::tag::active_camera>(view.begin(), view.end());
        registry_.emplace<component::tag::active_camera>(entity_);
        return *this;
      }

    private:
      entt::registry& registry_;
      entt::entity entity_;
      component::perspective_camera* camera_;
      component::transform* transform_;
  };
}

#endif 
