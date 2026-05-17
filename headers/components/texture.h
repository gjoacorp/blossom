#ifndef BLOSSOM_COMPONENT_TEXTURE_H
#define BLOSSOM_COMPONENT_TEXTURE_H

#include <string>

namespace blossom::component
{
  struct texture
  {
    int            count = 1;
    unsigned int   names = 0;

    unsigned int    target = 0x0DE1;   //  GL_TEXTURE_2D
    
    int             alignment = 1;
    int             lod = 0;

    std::string     path;
    unsigned int    internal_format;
    unsigned int    format;
    int             flip = 1;

  };
}

#endif 
