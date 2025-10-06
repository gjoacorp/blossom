#ifndef BLOSSOM_ENTITY_MANAGER_H
#define BLOSSOM_ENTITY_MANAGER_H

#include <cstdint>
#include <limits>
#include <concepts>
#include <queue>
#include <stdexcept>

namespace blossom
{
  template<std::unsigned_integral id_type = std::uint16_t>
  class entity_manager 
  {
    public:
      auto create_entity() -> id_type
      {
        if ( !recycled_ids_.empty() )
        {
          const id_type ENTITY_ID = recycled_ids_.front();
          recycled_ids_.pop();
          return ENTITY_ID;
        }

        if ( next_available_id_ == std::numeric_limits<id_type>::max() )
        {
          throw std::runtime_error("BLOSSOM_ERROR: Cannot create a new entity. Maximum number of entities reached.");
        }
        return next_available_id_++;
      }

      void destroy_entity(id_type entity)
      {
        if ( entity >= next_available_id_ )
        {
          throw std::invalid_argument("BLOSSOM_ERROR: Cannot destroy an invalid entity ID.");
        }
        recycled_ids_.push(entity);
      }

    private:
      id_type next_available_id_ = 0; 
      std::queue<id_type> recycled_ids_;
  };
}

#endif  
