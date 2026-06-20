#ifndef BLOSSOM_SYSTEM_RENDER_H
#define BLOSSOM_SYSTEM_RENDER_H

#include <iostream>

#include "../components/tags/active_camera.h"
#include "../components/matrices/transform.h"
#include "../components/matrices/view.h"
#include "../components/matrices/projection.h"
#include "../components/mesh.h"
#include "../components/camera.h"

#include <entt/entt.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace blossom::system
{
  class render
  {
    public:
      static void update(entt::registry& registry)
      {
        std::array<glm::mat4, 3> pvm_matrices;

        auto active_camera_view = registry.view<component::tag::active_camera>();
        bool active_camera_exists = !active_camera_view.empty();

        if (active_camera_exists)
        {
          auto active_camera_entity = active_camera_view.front();

          if (auto* projection = registry.try_get<component::matrix::projection>(active_camera_entity))
          {
            pvm_matrices[0] = projection->data;
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::projection." << "\n";
          }

          if (auto* view = registry.try_get<component::matrix::view>(active_camera_entity))
          {
            pvm_matrices[1] = view->data;
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::matrix::view." << "\n";
          }

          GLuint ubo = (registry.try_get<component::camera>(active_camera_entity))->ubo;
          glNamedBufferSubData(ubo, 0, sizeof(glm::mat4), glm::value_ptr(pvm_matrices[0]));
          glNamedBufferSubData(ubo, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(pvm_matrices[1]));
        }
        else
        {
          std::cout << "WARNING (blossom::system::render): No active camera detected. Drawing without a camera." << "\n";
        }

        auto mesh_view = registry.view<component::matrix::transform, component::mesh>();
        for ( auto [entity, matrix_transform, mesh] : mesh_view.each() )
        {
          pvm_matrices[2] = matrix_transform.data;
          draw_(mesh, pvm_matrices);
        }
      }

    private:
      static void draw_(const component::mesh& mesh, const std::array<glm::mat4, 3>& mvp_matrix)
      {
        glUseProgram(mesh.shader_program);
        glUniformMatrix4fv(
            mesh.model_uniform_location, 
            1, 
            GL_FALSE, 
            glm::value_ptr(mvp_matrix[2])
        );

        glBindVertexArray(mesh.vao);
        glPolygonMode(GL_FRONT_AND_BACK, mesh.polygon_mode);

        if ( !(mesh.index_count == 0) ) 
        { 
          glDrawElements(
              mesh.primitive_type, 
              mesh.index_count,
              GL_UNSIGNED_INT, 
              nullptr
              ); 
        }
        else 
        { 
          glDrawArrays(
              mesh.primitive_type, 
              0, 
              mesh.vertex_count
              ); 
        }
      }
  };
}

#endif 
