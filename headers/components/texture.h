#ifndef BLOSSOM_COMPONENT_TEXTURE_H
#define BLOSSOM_COMPONENT_TEXTURE_H

#include <string>

namespace blossom::component
{
  struct texture
  {
    // description: the total number of textures to generate when system::texture::init() is called
    // default    : 1
    // reference:   https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
    int count = 1;

    // description: stores the names of the generated textures
    // default    : 0
    // reference:   https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
    unsigned int names = 0;

    // description: specifies the texture target
    // default    : GL_TEXTURE_2D ( 0x0DE1 )
    // reference  : https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
    unsigned int target = 0x0DE1;

    // description: specifies the alignment requirements for the start of each pixel row in memory.
    // default    : 1
    // reference  : https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glPixelStorei.xml
    int pixel_alignment = 1;

    // description: specifies the level of detail. level n is the nth mipmap reduction image (level 0 is the base image).
    // default    : 0 
    // reference  : https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
    int level_of_detail = 0;

    // description: path to the image to be used as a texture
    // default    : ""
    // reference  : N/A
    std::string path;

    // description: should the image be flipped on load (yes = 1, no = 0).
    // default    : 1
    // reference  : N/A
    int flip_vertically_on_load = 1;

    // description: specifies the number of colour components in the texture
    // default    : GL_RGBA ( 0x1908 )
    // reference  : https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
    unsigned int internal_format   = 0x1908;

    // description: specifies the format of the pixel data.
    // default    : 0x1908 (GL_RGBA)
    // reference  : https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
    unsigned int pixel_data_format = 0x1908;
  };
}

#endif 
