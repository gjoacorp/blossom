#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/mesh.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Triangle Example";

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

  std::vector<glm::vec3> triangle_vertices =
  {
    { 0.0F,   0.577F,  0.0F},
    {-0.5F,  -0.289F,  0.0F},
    { 0.5F,  -0.289F,  0.0F}
  };

  const glm::vec3 TRIANGLE_SCALE {200.0F, 200.0F, 200.0F};

  entt::registry registry;

  constexpr glm::vec3 CAMERA_POSITION = { 0.0F, 0.0F, 5.0F };

  blossom::factory::camera{registry}
    .with_width  (WINDOW_WIDTH)
    .with_height (WINDOW_HEIGHT)
    .with_position (CAMERA_POSITION)
    .make_active();

  blossom::factory::mesh(registry)
    .with_vertices(triangle_vertices)
    .with_scale(TRIANGLE_SCALE)
    .with_shader_program(SHADER_PROGRAM_ID)
    .build();

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
