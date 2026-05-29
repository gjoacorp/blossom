#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/transform.h"
#include "../headers/systems/camera.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/sphere.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* window_title = "Blossom Mesh View Example";

auto main() -> int
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  entt::registry registry;

  constexpr glm::vec3 CAMERA_POSITION = { 0.0F, 1.0F, 1.0F };
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
    .vertex_shader_path   = "shaders/default.vert",
    .fragment_shader_path = "shaders/random.frag"
  };

  const GLuint SHADER_PROGRAM_ID = blossom::shader::compile(SHADER_INFO);

  blossom::factory::sphere(
      registry,
      1.0F,
      32,
      16,
      SHADER_PROGRAM_ID);

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
