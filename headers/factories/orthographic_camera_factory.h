#ifndef BLOSSOM_ORTHOGRAPHIC_CAMERA_FACTORY_H
#define BLOSSOM_ORTHOGRAPHIC_CAMERA_FACTORY_H

#include <entt/entt.hpp>
#include "../components/transform_c.h"
#include "../components/camera_c.h"

namespace blossom::factory
{
  class orthographic_camera
  {
    public:
      explicit orthographic_camera(entt::registry& registry) 
        : registry_(registry)
      {
        entity_    =  registry_.create();
        camera_    = &registry_.emplace<camera_c>(entity_);
        transform_ = &registry_.emplace<transform_c>(entity_);

        camera_->type = camera_type::ORTHOGRAPHIC;
      }

      auto with_width(const uint16_t width) -> orthographic_camera&
      {
        width_ = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> orthographic_camera&
      {
        height_ = height;
        return *this;
      }

      auto build() -> entt::entity
      {
        camera_->width  = width_;
        camera_->height = height_;
        camera_->near   = near_;
        camera_->far    = far_;
        return entity_;
      }

    private:
      static constexpr uint16_t DEFAULT_WIDTH  = 800;
      static constexpr uint16_t DEFAULT_HEIGHT = 600;
      static constexpr float DEFAULT_NEAR =   0.00F;
      static constexpr float DEFAULT_FAR  = 100.00F;

      uint16_t width_  = DEFAULT_WIDTH;
      uint16_t height_ = DEFAULT_HEIGHT;

      float near_ = DEFAULT_NEAR;
      float far_  = DEFAULT_FAR;

      entt::registry& registry_;
      entt::entity    entity_;
      camera_c*       camera_;
      transform_c*    transform_;
  };
}

#endif 
