#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/camera.h"
#include "../headers/systems/transform.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/rectangle.h"
#include "../headers/factories/cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

constexpr unsigned int WINDOW_WIDTH  = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Rectangle Camera ECS Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("resources/textures/couchy.png", &width, &height, &nrChannels, 0);
  if (data)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture." << std::endl;
  }
  stbi_image_free(data);

  blossom::shader default_shader {"shaders/texture.frag", "shaders/texture.vert"};

  GLint texture_uniform_location = glGetUniformLocation(default_shader.program_id, "Texture");
  glUniform1i(texture_uniform_location, 0);

  entt::registry registry;

  constexpr glm::vec3 RECTANGLE_POSITION = { 0.0F, 0.0F, 0.0F };
  constexpr glm::vec2 RECTANGLE_SCALE    = { 200.0F, 100.0F };

  constexpr glm::vec3 CAMERA_POSITION = { 0.0F, 0.0F, 5.0F };

  blossom::factory::rectangle(
      registry, 
      RECTANGLE_POSITION, 
      RECTANGLE_SCALE,
      default_shader.program_id);

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
    glBindTexture(GL_TEXTURE_2D, texture);

    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
