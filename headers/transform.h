#ifndef BLOSSOM_TRANSFORM_H
#define BLOSSOM_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace blossom
{
  class transform
  {
    public:
      glm::vec3 position = {0.0f, 0.0f, 0.0f};
      glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
      glm::vec3 scale    = {1.0f, 1.0f, 1.0f};

      transform(const glm::vec3& position) : position(position) {}
      transform() {}

      glm::mat4 calc_model_matrix() const
      {
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, position);
        model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model_matrix = glm::scale(model_matrix, scale);
        return model_matrix;
      }
  };
}

#endif 
