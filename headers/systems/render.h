#ifndef BLOSSOM_SYSTEM_RENDER_H
#define BLOSSOM_SYSTEM_RENDER_H

#include <entt/entt.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../components/orthographic_camera.h"
#include "../components/tags/active_camera.h"
#include "../components/perspective_camera.h"
#include "../components/transform.h"
#include "../components/mesh.h"

namespace blossom::system
{
  class render
  {
    public:
      static void update(entt::registry& registry)
      {
        glm::mat4 view_matrix(1.0F);
        glm::mat4 projection_matrix(1.0F);

        auto active_camera_view = registry.view<component::tag::active_camera>();
        bool active_camera_exists = !active_camera_view.empty();

        if (active_camera_exists)
        {
          auto active_camera_entity = active_camera_view.front();

          // Checking whether the active camera is an orthographic camera
          if (auto* orthographic_camera = registry.try_get<component::orthographic_camera>(active_camera_entity))
          {
            view_matrix = orthographic_camera->view_matrix;
            projection_matrix = orthographic_camera->projection_matrix;
          }
          // Checking whether the active camera is a perspective camera
          else if (auto* perspective_camera = registry.try_get<component::perspective_camera>(active_camera_entity))
          {
            view_matrix = perspective_camera->view_matrix;
            projection_matrix = perspective_camera->projection_matrix;
          }
        }
        else
        {
          std::cout << "WARNING (blossom::system::render): No active camera detected. Drawing without a camera." << "\n";
        }

        auto mesh_view = registry.view<component::transform, component::mesh>();
        for ( auto [entity, transform, mesh] : mesh_view.each() )
        {
          draw_(mesh, transform, view_matrix, projection_matrix);
        }
      }

    private:
      static void draw_(const component::mesh& mesh, const component::transform& transform, const glm::mat4& view_matrix, const glm::mat4& projection_matrix)
      {
        glUseProgram(mesh.shader_program);
        glUniformMatrix4fv(
            mesh.model_uniform_location, 
            1, 
            GL_FALSE, 
            glm::value_ptr( transform.matrix ) );

        glUniformMatrix4fv(
            mesh.view_uniform_location, 
            1, 
            GL_FALSE, 
            glm::value_ptr(view_matrix) );

        glUniformMatrix4fv(
            mesh.projection_uniform_location, 
            1, 
            GL_FALSE, 
            glm::value_ptr(projection_matrix) );

        glBindVertexArray(mesh.vao);
        glPolygonMode(GL_FRONT_AND_BACK, mesh.polygon_mode);

        if ( !mesh.indices.empty() ) 
        { 
          // this check is probably irrelevant
          if ( mesh.indices.size() > static_cast<size_t>(std::numeric_limits<GLsizei>::max()) )
          {
            throw std::runtime_error("ERROR: indices_.size() is too large to safely cast to GLsizei");
          }

          glDrawElements(
              mesh.primitive_type, 
              static_cast<GLsizei>( mesh.indices.size() ),
              GL_UNSIGNED_INT, 
              nullptr ); 
        }
        else 
        { 
          glDrawArrays(
              mesh.primitive_type, 
              0, 
              (GLsizei)mesh.vertices.size() ); 
        }
      }
  };
}

#endif 
