#include "../headers/window.h"
#include "../headers/perspective_camera.h"
#include "../headers/sphere.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const char* WINDOW_TITLE = "Blossom Mesh View Example";

int main()
{
    blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    const glm::vec3 camera_position = {0.0f, 1.0f, 1.0f};
    blossom::perspective_camera camera { camera_position, WINDOW_WIDTH, WINDOW_HEIGHT, 90.0f, 0.1f, 200.0f };
    camera.rotation.x = -45.0f;
    camera.update_view_matrix();

    blossom::shader shader("shaders/default.frag", "shaders/default.vert");

    blossom::sphere mesh{ shader.program_id };

    while (!glfwWindowShouldClose(window.window_ptr))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh.draw(&camera);
        glfwSwapBuffers(window.window_ptr); // swaps the front and back colour buffers
        glfwPollEvents();
    }

    window.destroy();
}
