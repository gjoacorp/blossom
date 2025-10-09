#include "../headers/window.h"
#include "../headers/shader.h"

#include "../headers/systems/camera_system.h"
#include "../headers/systems/transform_system.h"
#include "../headers/systems/mesh_system.h"
#include "../headers/systems/render_system.h"
#include "../headers/factories/orthographic_camera_factory.h"
#include "../headers/factories/mesh_factory.h"

constexpr unsigned int WINDOW_WIDTH  = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Rectangle Camera ECS Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
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

  constexpr glm::vec3 RECTANGLE_POSITION = { 500.0F, 500.0F, 0.0F };
  constexpr glm::vec3 RECTANGLE_SCALE    = { 200.0F, 100.0F, 1.0F };

  blossom::factory::mesh{registry}
    .with_position (RECTANGLE_POSITION)
    .with_scale    (RECTANGLE_SCALE)
    .with_vertices (rectangle_vertices)
    .with_indices  (rectangle_indices)
    .with_shader_program (rectangle_shader.program_id)
    .build();

  blossom::factory::orthographic_camera{registry}
    .with_width  (WINDOW_WIDTH)
    .with_height (WINDOW_HEIGHT)
    .build();

  while ( glfwWindowShouldClose(window.window_ptr) == 0 )
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
