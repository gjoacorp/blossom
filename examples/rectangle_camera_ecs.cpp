#include "../headers/window.h"
#include "../headers/shader.h"
#include <glm/fwd.hpp>
#include <vector>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "../headers/components/camera_c.h"
#include "../headers/components/transform_c.h"
#include "../headers/components/mesh_c.h"
#include "../headers/systems/camera_system.h"
#include "../headers/systems/transform_system.h"
#include "../headers/systems/mesh_system.h"
#include "../headers/systems/render_system.h"
#include "../headers/factories/orthographic_camera_factory.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* WINDOW_TITLE = "Blossom Rectangle Camera ECS Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  window.enter_fullscreen();

  blossom::shader rectangle_shader {"shaders/default.frag", "shaders/default.vert"};

  std::vector<glm::vec3> rectangle_vertices = 
  {
    glm::vec3{ 1.0F,  1.0F, 0.0F}, 
    glm::vec3{-1.0F,  1.0F, 0.0F}, 
    glm::vec3{-1.0F, -1.0F, 0.0F},
    glm::vec3{ 1.0F, -1.0F, 0.0F} 
  };

  std::vector<GLuint> rectangle_indices = 
  {
    0, 1, 2, 
    0, 2, 3 
  };

  entt::registry registry;

  // Rectangle
  auto rectangle_entity = registry.create();
  auto &rectangle_transform = registry.emplace<transform_c>(rectangle_entity);
  auto &rectangle_mesh = registry.emplace<mesh_c>(rectangle_entity);

  rectangle_transform.position = {500.0f, 500.0f, 0.0f};
  rectangle_transform.scale    = {200.0f, 100.0f, 1.0f};

  rectangle_mesh.vertices = rectangle_vertices;
  rectangle_mesh.indices  = rectangle_indices;
  rectangle_mesh.shader_program = rectangle_shader.program_id;

  blossom::factory::orthographic_camera{registry}
    .with_width  (WINDOW_WIDTH)
    .with_height (WINDOW_HEIGHT)
    .build();

  while ( !glfwWindowShouldClose(window.window_ptr) )
  {
    blossom::transform_system::update(registry);
    blossom::camera_system::update(registry);
    blossom::mesh_system::update(registry);

    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR.data());
    blossom::render_system::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
