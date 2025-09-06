#ifndef MESH
#define MESH

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class mesh
{
  public:
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;

    void draw() const;

    mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program);
    mesh(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, GLuint shader_program);
    ~mesh();

    void init();

  private:
    GLuint shader_program_;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint ibo_ = 0;
};

#endif
