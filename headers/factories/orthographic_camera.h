#ifndef BLOSSOM_FACTORY_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_FACTORY_ORTHOGRAPHIC_CAMERA_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/orthographic_camera.h"
#include "../components/tags/active_camera.h"

namespace blossom::factory
{
  class orthographic_camera
  {
    public:
      explicit orthographic_camera(entt::registry& registry) : registry_(registry)
      {
        entity_                 =  registry_.create();
        orthographic_camera_    = &registry_.emplace<component::orthographic_camera>(entity_);
        transform_              = &registry_.emplace<component::transform>(entity_);
      }

      auto with_width(const uint16_t width) -> orthographic_camera&
      {
        orthographic_camera_->width = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> orthographic_camera&
      {
        orthographic_camera_->height = height;
        return *this;
      }

      auto with_position(const glm::vec3& position)
      {
        transform_->position = position;
        return *this;
      }

      auto with_rotation(const glm::vec3& rotation)
      {
        transform_->rotation = rotation;
        return *this;
      }

      auto make_active() -> orthographic_camera&
      {
        auto view = registry_.view<component::tag::active_camera>();
        registry_.remove<component::tag::active_camera>(view.begin(), view.end());
        registry_.emplace<component::tag::active_camera>(entity_);
        return *this;
      }

    private:
      entt::registry& registry_;
      entt::entity entity_;

      component::orthographic_camera* orthographic_camera_;
      component::transform* transform_;
  };
}

#endif 
