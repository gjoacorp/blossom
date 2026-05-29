#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/grid.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Waves Example";

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  entt::registry registry;

  constexpr glm::vec3 CAMERA_POSITION = { 25.0F, 7.5F, 25.0F};
  constexpr glm::vec3 CAMERA_ROTATION = {-45.0F, 0.0F,  0.0F};

  constexpr float CAMERA_FOV_Y = 90.0F;

  blossom::factory::camera{registry}
  .with_width (WINDOW_WIDTH)
    .with_height(WINDOW_HEIGHT)
    .with_fov_y (CAMERA_FOV_Y)
    .with_position(CAMERA_POSITION)
    .with_rotation(CAMERA_ROTATION)
    .with_type(blossom::component::camera::camera_type::PERSPECTIVE)
    .make_active();

  const blossom::shader_info SHADER_INFO
  {
    .vertex_shader_path   = "shaders/waves.vert",
    .fragment_shader_path = "shaders/waves.frag"
  };

  const GLuint SHADER_PROGRAM_ID = blossom::shader::compile(SHADER_INFO);
  GLint time_uniform_location = glGetUniformLocation(SHADER_PROGRAM_ID, "time");

  constexpr uint32_t TOTAL_GRID_TILES = 500;
  constexpr glm::vec2 GRID_TILE_WIDTH = {0.25F, 0.25F};

  blossom::factory::grid(
      registry,
      TOTAL_GRID_TILES,
      GRID_TILE_WIDTH,
      SHADER_PROGRAM_ID);

  blossom::system::transform::update(registry);
  blossom::system::camera::update(registry);

  while (glfwWindowShouldClose(window.window_ptr) == 0) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform1f(time_uniform_location, static_cast<float>(glfwGetTime()));
    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr); 
    glfwPollEvents();
  }
  window.destroy();
}
