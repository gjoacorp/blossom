#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render.h"
#include "../headers/systems/camera.h"
#include "../headers/systems/transform.h"
#include "../headers/factories/camera.h"
#include "../headers/factories/rectangle.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

constexpr unsigned int WINDOW_WIDTH  = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Texture Loading Example";

const std::array<GLfloat,4> CLEAR_COLOR = { 0.0F, 0.0F, 0.0F, 1.0F};

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  constexpr GLsizei NUMBER_OF_TEXTURES = 1;
  GLuint                  texture_name = 0;

  glGenTextures(1, &texture_name);
  glBindTexture(GL_TEXTURE_2D, texture_name);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int texture_width    = 0;
  int texture_height   = 0;
  int texture_channels = 0;

  const std::string TEXTURE_PATH = "resources/textures/couchy.png";

  stbi_set_flip_vertically_on_load(1);

  unsigned char* data = stbi_load(TEXTURE_PATH.c_str(), &texture_width, &texture_height, &texture_channels, 0);

  if (data != nullptr)
  {
    constexpr GLint ALIGNMENT = 1;
    constexpr GLint LOD      =  0;

    glPixelStorei(GL_UNPACK_ALIGNMENT, ALIGNMENT);
    glTexImage2D(
        GL_TEXTURE_2D, 
        LOD, 
        GL_RGB, 
        texture_width, 
        texture_height, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "WARNING: Failed to load texture from " + TEXTURE_PATH + ".\n";
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
    glBindTexture(GL_TEXTURE_2D, texture_name);

    blossom::system::render::update(registry);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
