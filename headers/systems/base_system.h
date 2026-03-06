#ifndef BLOSSOM_SYSTEM_BASE_SYSTEM_H
#define BLOSSOM_SYSTEM_BASE_SYSTEM_H

#include <entt/entt.hpp>

namespace blossom::system
{
  template <typename T>
  class base_system
  {
    public:

      static void init(entt::registry& registry) 
      {
        T::init_impl_(registry);
      }

      static void update(entt::registry& registry) 
      {
        T::update_impl_(registry);
      }

    protected:

      static void init_impl_(entt::registry& registry) {}

      static void update_impl_(entt::registry& registry) {}

      static void on_construct_(entt::registry& registry, entt::entity entity)
      {
        T::on_construct_impl_(registry, entity);
      }

      static void on_construct_impl_(entt::registry& registry, entt::entity entity) {}
  };
};

#endif 
