#include "../headers/window.h"
#include "../headers/perspective_camera.h"
#include "../headers/sphere.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const char* WINDOW_TITLE = "Blossom Mesh View Example";

glm::vec3 lightColor = {1.0f, 1.0f, 1.0f};
glm::vec3 objectColor = {1.0f, 0.5f, 0.31f};

int main()
{
    blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    const glm::vec3 camera_position = {0.0f, 2.0f, 2.0f};
    blossom::perspective_camera camera { camera_position, WINDOW_WIDTH, WINDOW_HEIGHT, 90.0f, 0.1f, 200.0f };
    camera.rotation.x = -45.0f;
    camera.update_view_matrix();

    blossom::shader shader("shaders/default_lit.frag", "shaders/default.vert");

    blossom::shader lighting_shader("shaders/light.frag", "shaders/default.vert");

    blossom::sphere mesh{ shader.program_id };
    mesh.scale = {0.5f, 0.5f, 0.5f};

    blossom::sphere light{ lighting_shader.program_id };
    light.scale = {0.5f, 0.5f, 0.5f};
    light.position = {1.0f, 0.8f, 1.0f};

    while (!glfwWindowShouldClose(window.window_ptr))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light.draw(&camera);
        mesh.draw(&camera);
        mesh.set_vec3("objectColor", objectColor);
        mesh.set_vec3("lightColor", lightColor);
        mesh.set_vec3("lightPos", light.position);

        glfwSwapBuffers(window.window_ptr); // swaps the front and back colour buffers
        glfwPollEvents();
    }

    window.destroy();
}
