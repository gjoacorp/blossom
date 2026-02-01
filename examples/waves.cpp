#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/mesh.h"
#include "../headers/systems/perspective_camera.h"
#include "../headers/factories/perspective_camera.h"
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

  blossom::factory::perspective_camera{registry}
    .with_width (WINDOW_WIDTH)
    .with_height(WINDOW_HEIGHT)
    .with_fov_y (CAMERA_FOV_Y)
    .with_position(CAMERA_POSITION)
    .with_rotation(CAMERA_ROTATION)
    .make_active();

  blossom::shader waves_shader("shaders/waves.frag", "shaders/waves.vert");
  GLint time_uniform_location = glGetUniformLocation(waves_shader.program_id, "time");

  constexpr uint32_t TOTAL_GRID_TILES = 500;
  constexpr glm::vec2 GRID_TILE_WIDTH = {0.25F, 0.25F};

  blossom::factory::grid(
      registry,
      TOTAL_GRID_TILES,
      GRID_TILE_WIDTH,
      waves_shader.program_id);

  blossom::system::mesh::init(registry);
  blossom::system::transform::update(registry);
  blossom::system::perspective_camera::update(registry);

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
