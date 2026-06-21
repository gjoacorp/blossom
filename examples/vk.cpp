#include "../headers/window.h"
#include "../headers/vk_renderer.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* window_title = "Blossom Vulkan Example";

auto main() -> int 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
  window.enter_fullscreen();

  blossom::system::vk_renderer::create_instance_();
}
