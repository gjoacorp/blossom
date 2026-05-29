#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/camera.h"
#include "../headers/systems/transform.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/rectangle.h"
#include "../headers/systems/texture.h"

constexpr unsigned int WINDOW_WIDTH  = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Texture Loading Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  const blossom::shader_info SHADER_INFO
  {
    .vertex_shader_path = "shaders/texture.vert",
    .fragment_shader_path = "shaders/texture.frag"
  };
  const auto DEFAULT_SHADER = blossom::shader::compile(SHADER_INFO);

  entt::registry registry;

  constexpr glm::vec3 RECTANGLE_POSITION = { 0.0F, 0.0F, 0.0F };
  constexpr glm::vec2 RECTANGLE_SCALE    = { 200.0F, 100.0F };

  auto rectangle = blossom::factory::rectangle(
      registry, 
      RECTANGLE_POSITION, 
      RECTANGLE_SCALE,
      DEFAULT_SHADER);

  auto& texture_component = registry.emplace<blossom::component::texture>(rectangle);
  texture_component.path = "resources/textures/couchy.png";
  texture_component.internal_format = GL_RGB;
  texture_component.format = GL_RGBA;

  blossom::system::texture::init(registry);

  GLint texture_uniform_location = glGetUniformLocation(DEFAULT_SHADER, "Texture");
  glUniform1i(texture_uniform_location, 0);

  constexpr glm::vec3 CAMERA_POSITION = { 0.0F, 0.0F, 5.0F };

  blossom::factory::camera{registry}
    .with_width    (WINDOW_WIDTH)
    .with_height   (WINDOW_HEIGHT)
    .with_position (CAMERA_POSITION)
    .make_active();

  blossom::system::transform::update(registry);
  blossom::system::camera::update(registry);

  while ( glfwWindowShouldClose(window.window_ptr) == 0 )
  {
    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(texture_component.target, texture_component.names);

    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
