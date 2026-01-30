#ifndef BLOSSOM_FACTORY_CAMERA_H
#define BLOSSOM_FACTORY_CAMERA_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/camera.h"

namespace blossom::factory
{
  class camera
  {
    public:
      explicit camera(entt::registry& registry) 
        : registry_(registry)
      {
        entity_    =  registry_.create();
        camera_    = &registry_.emplace<component::camera>(entity_);
        transform_ = &registry_.emplace<component::transform>(entity_);
      }

      auto with_type(const component::camera_type type)
      {
        camera_->type = type;
        return *this;
      }

      auto with_width(const uint16_t width) -> camera&
      {
        camera_->width = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> camera&
      {
        camera_->height = height;
        return *this;
      }

      auto with_fov_y(float fov_y) -> camera&
      {
        camera_->fov_y = fov_y;
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

    private:
      entt::registry&       registry_;
      entt::entity          entity_;
      component::camera*    camera_;
      component::transform* transform_;
  };
}

#endif 
