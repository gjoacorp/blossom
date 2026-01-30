#include "../headers/window.h"
#include "../headers/shader.h"

#include "../headers/systems/render.h"
#include "../headers/systems/mesh.h"
#include "../headers/systems/camera.h"
#include "../headers/systems/transform.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/rectangle.h"

constexpr unsigned int WINDOW_WIDTH  = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Rectangle Camera ECS Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  blossom::shader rectangle_shader {"shaders/default.frag", "shaders/default.vert"};

  entt::registry registry;

  constexpr glm::vec3 RECTANGLE_POSITION = { 500.0F, 500.0F, 0.0F };
  constexpr glm::vec2 RECTANGLE_SCALE    = { 200.0F, 100.0F };

  blossom::factory::rectangle(
      registry, 
      RECTANGLE_POSITION, 
      RECTANGLE_SCALE,
      rectangle_shader.program_id);

  blossom::factory::camera{registry}
    .with_width  (WINDOW_WIDTH)
    .with_height (WINDOW_HEIGHT);

  blossom::system::camera::update(registry);
  blossom::system::transform::update(registry);
  blossom::system::mesh::init(registry);

  while ( glfwWindowShouldClose(window.window_ptr) == 0 )
  {
    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR.data());
    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
