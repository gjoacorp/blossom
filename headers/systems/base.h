#ifndef BLOSSOM_SYSTEM_BASE_H
#define BLOSSOM_SYSTEM_BASE_H

#include <entt/entt.hpp>
#include <concepts>

namespace blossom::system
{
  template <typename T>
    concept implements_update_implementation_ = requires(entt::registry& registry)
    {
      { T::update_implementation_(registry) } -> std::same_as<void>; 
    };

  template <typename T>
    concept implements_init_implementation_ = requires(entt::registry& registry)
    {
      { T::init_implementation_(registry) } -> std::same_as<void>;   
    };

  template <typename T>
    class base
    {
      public:
        static void update(entt::registry& registry)
        {
          static_assert(implements_update_implementation_<T>,
              "ERROR (blossom::system::base): Systems deriving from base MUST implement update_implementation_().");

          T::update_implementation_(registry);
        }

        static void init(entt::registry& registry)
        {
          static_assert(implements_init_implementation_<T>,
              "ERROR (blossom::system::base): Systems deriving from base MUST implement init_implementation_().");

          T::init_implementation_(registry);
        }
    };
}

#endif
