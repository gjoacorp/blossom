#include "../headers/window.h"
#include "../headers/shader.h"
#include "../headers/systems/render_system.h"
#include "../headers/systems/transform_system.h"
#include "../headers/systems/camera_system.h"
#include "../headers/systems/mesh_system.h"
#include "../headers/factories/camera_factory.h"
#include "../headers/factories/sphere_factory.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const char* window_title = "Blossom Mesh View Example";

auto main() -> int
{
    blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    entt::registry registry;

    constexpr glm::vec3 CAMERA_POSITION = { 0.0f, 1.0f, 1.0f };
    constexpr glm::vec3 CAMERA_ROTATION = {-45.0F, 0.0F,  0.0F};

    constexpr float CAMERA_FOV_Y = 90.0F;

    blossom::factory::camera{registry}
    .with_type(camera_type::PERSPECTIVE)
       .with_width (WINDOW_WIDTH)
       .with_height(WINDOW_HEIGHT)
       .with_fov_y (CAMERA_FOV_Y)
       .with_position(CAMERA_POSITION)
       .with_rotation(CAMERA_ROTATION)
       .build();

    blossom::shader waves_shader("shaders/default.frag", "shaders/default.vert");

    blossom::factory::sphere(
          registry,
          1.0f,
          32,
          16,
          waves_shader.program_id);


    blossom::mesh_system::init(registry);
    blossom::transform_system::update(registry);
    blossom::camera_system::update(registry);

    while (glfwWindowShouldClose(window.window_ptr) == 0) 
    {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       blossom::render_system::update(registry);
       glfwSwapBuffers(window.window_ptr); 
       glfwPollEvents();
    }
    window.destroy();
}
