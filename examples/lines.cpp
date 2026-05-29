#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/systems/render.h"
#include "../headers/factories/camera.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/line.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Line Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  const blossom::shader_info SHADER_INFO
  {
    .vertex_shader_path   = "shaders/default.vert",
    .fragment_shader_path = "shaders/default.frag"
  };

  const GLuint SHADER_PROGRAM_ID = blossom::shader::compile(SHADER_INFO);

  // Vertices (start and end points) for a line
  const glm::vec3 LINE_START_POINT = {-200.0F, 0.0F, 0.0F};
  const glm::vec3 LINE_END_POINT   = { 200.0F, 0.0F, 0.0F};

  // Vertices for a line strip
  std::vector<glm::vec3> line_strip_points = 
  {
    {-200.0F, 100.0F, 0.0F},
    {-100.0F,  50.0F, 0.0F},
    {   0.0F, 100.0F, 0.0F},
    {100.0F,   50.0F, 0.0F},
    {200.0F,  100.0F, 0.0F}
  };

  const glm::vec3 CAMERA_POSITION = { 0.0F, 0.0F, 5.0F };

  entt::registry registry;

  blossom::factory::camera{registry}
    .with_width    (WINDOW_WIDTH)
    .with_position (CAMERA_POSITION)
    .with_height   (WINDOW_HEIGHT)
    .make_active();

  blossom::factory::line(
      registry,
      SHADER_PROGRAM_ID,
      LINE_START_POINT,
      LINE_END_POINT);

  blossom::factory::line(
      registry,
      SHADER_PROGRAM_ID,
      line_strip_points);

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
