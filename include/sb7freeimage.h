#ifndef __SB7_FREE_IMAGE_H__
#define __SB7_FREE_IMAGE_H__


#include <freeimage.h>
#include <sb7.h>
#include <malloc.h>

namespace sb7
{
namespace freeimage
{
typedef struct   
{  
    unsigned int         w;  
    unsigned int             h;  
    unsigned char           *buf;  
    unsigned int          rgb_mode;  
}GLBITMAP;

unsigned int loadtexture(const char *filename);
}
}

#endif