#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/systems/mesh.h"
#include "../headers/systems/render.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/mesh.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/line.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Triangle Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  blossom::shader default_shader {"shaders/default.frag", "shaders/default.vert"};

  const glm::vec3 LINE_START = {-200.0F, 0.0F, 0.0F};
  const glm::vec3 LINE_END   = { 200.0F, 0.0F, 0.0F};

  const glm::vec3 CAMERA_POSITION = { 0.0F, 0.0F, 5.0F };

  entt::registry registry;

  blossom::factory::camera{registry}
    .with_type     (blossom::component::camera_type::ORTHOGRAPHIC)
    .with_width    (WINDOW_WIDTH)
    .with_position (CAMERA_POSITION)
    .with_height   (WINDOW_HEIGHT);

  blossom::factory::line(
      registry,
      default_shader.program_id,
      LINE_START,
      LINE_END);

  blossom::system::mesh::init(registry);
  blossom::system::transform::update(registry);
  blossom::system::camera::update(registry);

  while ( glfwWindowShouldClose(window.window_ptr) == 0 )
  {
    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR.data());
    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
}
