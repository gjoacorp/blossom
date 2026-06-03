#ifndef BLOSSOM_SYSTEM_TEXTURE_H
#define BLOSSOM_SYSTEM_TEXTURE_H

#include "../components/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb/stb_image.h"

#include <entt/entt.hpp>

#include <string>
#include <iostream>
#include <glad/gl.h>

namespace blossom::system
{
  class texture
  {
    public:
      static void init(entt::registry& registry)
      {
        auto view = registry.view<component::texture>();
        for ( auto [entity, texture] : view.each() )
        {
          glGenTextures(texture.count, &texture.names);
          glBindTexture(texture.target, texture.names);

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          
          with_image(texture, texture.path, texture.internal_format, texture.pixel_data_format, texture.flip_vertically_on_load);
        }
      }

      static void with_image(blossom::component::texture &texture, const std::string path, unsigned int internal_format, unsigned int format, int flip)
      {
        if ( !path.empty() )
        {
          stbi_set_flip_vertically_on_load(flip);

          int _width    = 0;
          int _height   = 0;
          int _channels = 0;

          unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);

          if (data != nullptr)
          {
            glPixelStorei(GL_UNPACK_ALIGNMENT, texture.pixel_alignment);
            glTexImage2D(
                texture.target, 
                texture.level_of_detail, 
                internal_format, 
                _width, 
                _height, 
                0, 
                format, 
                GL_UNSIGNED_BYTE, 
                data);
            glGenerateMipmap(texture.target);
          }
          else
          {
            std::cout << "WARNING: Failed to load texture from " + path + ".\n";
          }
          stbi_image_free(data);
        }
      }

    private:
  };
}

#endif 
