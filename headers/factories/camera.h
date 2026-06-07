#ifndef BLOSSOM_FACTORY_CAMERA_H
#define BLOSSOM_FACTORY_CAMERA_H

#include <entt/entt.hpp>
#include "../components/transform.h"
#include "../components/matrices/transform.h"
#include "../components/matrices/view.h"
#include "../components/matrices/projection.h"
#include "../components/camera.h"
#include "../components/tags/active_camera.h"

namespace blossom::factory
{
  class camera
  {
    public:
      explicit camera(entt::registry& registry) 
        : registry_(registry)
      {
        entity_    =  registry_.create();
        registry_.emplace<component::camera>(entity_);
        registry_.emplace<component::transform>(entity_);
        registry_.emplace<component::matrix::transform>(entity_);
        registry_.emplace<component::matrix::view>(entity_);
        registry_.emplace<component::matrix::projection>(entity_);

        init_buffers();
      }

      void init_buffers()
      {
        auto& ubo = registry_.get<component::camera>(entity_).ubo;
        glCreateBuffers(1, &ubo);
        glNamedBufferData(ubo, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
      }

      auto with_width(const uint16_t width) -> camera&
      {
        registry_.get<component::camera>(entity_).width = width;
        return *this;
      }

      auto with_height(const uint16_t height) -> camera&
      {
        registry_.get<component::camera>(entity_).height = height;
        return *this;
      }

      auto with_fov_y(float fov_y) -> camera&
      {
        registry_.get<component::camera>(entity_).fov_y = fov_y;
        return *this;
      }

      auto with_position(const glm::vec3& position) -> camera&
      {
        registry_.get<component::transform>(entity_).position = position;
        return *this;
      }

      auto with_rotation(const glm::vec3& rotation) -> camera&
      {
        registry_.get<component::transform>(entity_).rotation = rotation;
        return *this;
      }

      auto with_type(const component::camera::camera_type& type)
      {
        registry_.get<component::camera>(entity_).type = type;
        return *this;
      }

      auto make_active() -> camera&
      {
        auto view = registry_.view<component::tag::active_camera>();
        registry_.remove<component::tag::active_camera>(view.begin(), view.end());
        registry_.emplace<component::tag::active_camera>(entity_);
        return *this;
      }

    private:
      entt::registry& registry_;
      entt::entity entity_;
  };
}

#endif 
