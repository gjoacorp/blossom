#include <gtest/gtest.h>
#include <stdexcept>
#include "../headers/entity_manager.h"

TEST(entity_manager_test, create_entity_exceeding_limit_throws)
{
  blossom::entity_manager<std::uint8_t> manager;

  for (std::size_t i = 0; i < std::numeric_limits<std::uint8_t>::max(); ++i)
  {
    manager.create_entity();
  }
  EXPECT_THROW(manager.create_entity(), std::runtime_error);
}

TEST(entity_manager_test, destroy_invalid_entity_throws)
{
  blossom::entity_manager<std::uint8_t> manager;
  manager.create_entity();
  EXPECT_THROW(manager.destroy_entity(5), std::invalid_argument);
}
