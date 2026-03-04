#ifndef BLOSSOM_SYSTEM_RENDER_H
#define BLOSSOM_SYSTEM_RENDER_H

#include <entt/entt.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../components/tags/active_camera.h"
#include "../components/view_projection_matrix.h"
#include "../components/transform_matrix.h"
#include "../components/mesh.h"

namespace blossom::system
{
  class render
  {
    public:
      static void update(entt::registry& registry)
      {
        glm::mat4 view_projection_matrix(1.0F);

        auto active_camera_view = registry.view<component::tag::active_camera>();
        bool active_camera_exists = !active_camera_view.empty();

        if (active_camera_exists)
        {
          auto active_camera_entity = active_camera_view.front();

          if (auto* vp_matrix = registry.try_get<component::view_projection_matrix>(active_camera_entity))
          {
            view_projection_matrix = vp_matrix->matrix;
          }
          else
          {
            std::cout << "WARNING (blossom::system::render): Active camera doesn't have component::view_projection_matrix." << "\n";
          }
        }
        else
        {
          std::cout << "WARNING (blossom::system::render): No active camera detected. Drawing without a camera." << "\n";
        }

        auto mesh_view = registry.view<component::transform_matrix, component::mesh>();
        for ( auto [entity, transform_matrix, mesh] : mesh_view.each() )
        {
          const auto MVP_MATRIX = transform_matrix.matrix * view_projection_matrix;
          draw_(mesh, MVP_MATRIX);
        }
      }

    private:
      static void draw_(const component::mesh& mesh, const glm::mat4& mvp_matrix)
      {
        glUseProgram(mesh.shader_program);
        glUniformMatrix4fv(
            mesh.model_uniform_location, 
            1, 
            GL_FALSE, 
            glm::value_ptr(mvp_matrix) );

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
