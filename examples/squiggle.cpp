#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/grid.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Geometry Shader Example";

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  entt::registry registry;

  constexpr glm::vec3 CAMERA_POSITION = {   3.0F,  5.0F,  5.0F};
  constexpr glm::vec3 CAMERA_ROTATION = { -60.0F,  0.0F,  0.0F};

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
    .vertex_shader_path   = "shaders/default.vert",
    .geometry_shader_path = "shaders/squiggle.geom",
    .fragment_shader_path = "shaders/default.frag"
  };

  const GLuint SHADER_PROGRAM_ID = blossom::shader::compile(SHADER_INFO);

  constexpr uint32_t TOTAL_GRID_TILES = 3;
  constexpr glm::vec2 GRID_TILE_WIDTH = {3.0F, 3.0F};

  auto grid = blossom::factory::grid(
      registry,
      TOTAL_GRID_TILES,
      GRID_TILE_WIDTH,
      SHADER_PROGRAM_ID);

  auto& mesh_component = registry.get<blossom::component::mesh>(grid);
  mesh_component.primitive_type = GL_POINTS;
  mesh_component.polygon_mode = GL_LINES;

  blossom::system::transform::update(registry);
  blossom::system::camera::update(registry);

  while (glfwWindowShouldClose(window.window_ptr) == 0) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr); 
    glfwPollEvents();
  }
  window.destroy();
}
