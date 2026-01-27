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
        type_ = type;
        return *this;
      }

      auto with_width(const uint16_t width) -> camera&
      {
        width_ = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> camera&
      {
        height_ = height;
        return *this;
      }

      auto with_fov_y(float fov_y) -> camera&
      {
        fov_y_ = fov_y;
        return *this;
      }

      auto with_position(const glm::vec3& position)
      {
        position_ = position;
        return *this;
      }

      auto with_rotation(const glm::vec3& rotation)
      {
        rotation_ = rotation;
        return *this;
      }

      auto build() -> entt::entity
      {
        camera_->width  = width_;
        camera_->height = height_;
        camera_->near   = near_;
        camera_->far    = far_;
        camera_->fov_y  = fov_y_;
        camera_->type   = type_;

        transform_->position = position_;
        transform_->rotation = rotation_;

        return entity_;
      }

    private:
      static constexpr uint16_t DEFAULT_WIDTH  = 800;
      static constexpr uint16_t DEFAULT_HEIGHT = 600;

      static constexpr float DEFAULT_NEAR   =   0.00F;
      static constexpr float DEFAULT_FAR    = 100.00F;
      static constexpr float DEFAULT_FOV_Y  =  90.00F;

      static constexpr component::camera_type DEFAULT_TYPE = component::camera_type::ORTHOGRAPHIC;

      uint16_t width_  = DEFAULT_WIDTH;
      uint16_t height_ = DEFAULT_HEIGHT;

      float near_  = DEFAULT_NEAR;
      float far_   = DEFAULT_FAR;
      float fov_y_ = DEFAULT_FOV_Y;

      glm::vec3 rotation_;
      glm::vec3 position_;

      component::camera_type type_ = DEFAULT_TYPE;

      entt::registry&       registry_;
      entt::entity          entity_;
      component::camera*    camera_;
      component::transform* transform_;
  };
}

#endif 
