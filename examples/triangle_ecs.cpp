#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/systems/mesh_system.h"
#include "../headers/systems/render_system.h"
#include "../headers/factories/orthographic_camera_factory.h"
#include "../headers/factories/mesh_factory.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Triangle Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  blossom::shader triangle_shader {"shaders/triangle.frag", "shaders/triangle.vert"};

  const std::vector<glm::vec3> TRIANGLE_VERTICES =
  {
    // NOLINTNEXTLINE(modernize-use-std-numbers)
    { 0.0F,   0.577F,  0.0F},
    {-0.5F,  -0.289F,  0.0F},
    { 0.5F,  -0.289F,  0.0F}
  };

  entt::registry registry;

  blossom::factory::orthographic_camera{registry}
    .with_width  (WINDOW_WIDTH)
    .with_height (WINDOW_HEIGHT)
    .build();

  blossom::factory::mesh(registry)
    .with_vertices(TRIANGLE_VERTICES)
    .with_shader_program(triangle_shader.program_id);

  blossom::mesh_system::init(registry);

  while ( glfwWindowShouldClose(window.window_ptr) == 0 )
  {
    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR.data());
    blossom::render_system::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
}
