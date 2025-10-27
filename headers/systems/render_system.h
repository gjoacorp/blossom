#ifndef BLOSSOM_RENDER_SYSTEM_H
#define BLOSSOM_RENDER_SYSTEM_H

#include <entt/entt.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../components/camera.h"
#include "../components/transform.h"
#include "../components/mesh.h"

namespace blossom
{
  class render_system
  {
    public:
      static void update(entt::registry& registry)
      {
        glm::mat4 view_matrix;
        glm::mat4 projection_matrix;

        auto camera_view = registry.view<component::transform, component::camera>();

        for (auto [camera_entity, camera_transform, camera] : camera_view.each() )
        {
          view_matrix = camera.view_matrix;
          projection_matrix = camera.projection_matrix;
          break;
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
              GL_TRIANGLES, 
              static_cast<GLsizei>( mesh.indices.size() ),
              GL_UNSIGNED_INT, 
              nullptr ); 
        }
        else 
        { 
          glDrawArrays(
              GL_TRIANGLES, 
              0, 
              (GLsizei)mesh.vertices.size() ); 
        }
      }
  };
}

#endif 
