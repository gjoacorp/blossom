#include "../headers/camera.h"

using blossom::camera;

camera::camera(const glm::vec3& position, uint16_t width, uint16_t height, float near, float far) : 
  transform(position), 
  width(width), 
  height(height), 
  near(near), 
  far(far) {}

void camera::update_view_matrix()
{
  view_matrix = glm::mat4(1.0F);
  view_matrix = glm::rotate(view_matrix, glm::radians(-rotation.z), glm::vec3(0.0F, 0.0F, 1.0F));
  view_matrix = glm::rotate(view_matrix, glm::radians(-rotation.y), glm::vec3(0.0F, 1.0F, 0.0F));
  view_matrix = glm::rotate(view_matrix, glm::radians(-rotation.x), glm::vec3(1.0F, 0.0F, 0.0F));
  view_matrix = glm::scale(view_matrix, scale); 
  view_matrix = glm::translate(view_matrix, -position);
}
