#include <sb7freeimage.h>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif /* _MSC_VER */

namespace sb7
{

namespace freeimage
{

GLBITMAP * FIBitmap2GLBitmap(FIBITMAP *fibmp)
{
	int i, j, k;
	int pitch = FreeImage_GetPitch(fibmp);
	unsigned char *bits = FreeImage_GetBits(fibmp);
	int bpp = FreeImage_GetBPP(fibmp);
	GLBITMAP *glbmp = (GLBITMAP *)malloc(sizeof(GLBITMAP));	
	RGBQUAD *palette = NULL;

	if ( !glbmp ) return NULL;
	
	glbmp->w = FreeImage_GetWidth(fibmp);
	glbmp->h = FreeImage_GetHeight(fibmp);	

	switch ( bpp ) {
	case 8:
		if ( !(palette = FreeImage_GetPalette(fibmp)) ) return NULL; 
		if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*3)) ) return NULL;
		glbmp->rgb_mode = GL_RGB;
		for ( i = 0; i < glbmp->h; ++i ) {
			for ( j = 0; j < glbmp->w; ++j ) {
				k = bits[i*pitch+j];
				glbmp->buf[(i*glbmp->w+j)*3+0] = palette[k].rgbRed;
				glbmp->buf[(i*glbmp->w+j)*3+1] = palette[k].rgbGreen;
				glbmp->buf[(i*glbmp->w+j)*3+2] = palette[k].rgbBlue;
			}
		}
		break;
	case 24:
		if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*3)) ) return NULL;
		glbmp->rgb_mode = GL_RGB;
		for ( i = 0; i < glbmp->h; ++i ) {
			for ( j = 0; j < glbmp->w; ++j ) {
				glbmp->buf[(i*glbmp->w+j)*3+0] = bits[i*pitch+j*3+2];
				glbmp->buf[(i*glbmp->w+j)*3+1] = bits[i*pitch+j*3+1];
				glbmp->buf[(i*glbmp->w+j)*3+2] = bits[i*pitch+j*3+0];
			}
		}
		break;
	case 32:
		if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*4)) ) return NULL;
		glbmp->rgb_mode = GL_RGBA;
		for ( i = 0; i < glbmp->h; ++i ) {
			for ( j = 0; j < glbmp->w; ++j ) {
				glbmp->buf[(i*glbmp->w+j)*4+0] = bits[i*pitch+j*4+2];
				glbmp->buf[(i*glbmp->w+j)*4+1] = bits[i*pitch+j*4+1];
				glbmp->buf[(i*glbmp->w+j)*4+2] = bits[i*pitch+j*4+0];
				glbmp->buf[(i*glbmp->w+j)*4+3] = bits[i*pitch+j*4+3];
			}
		}
		break;
	default: return NULL;	
	}

	return glbmp;
}

void FreeGLBitmap(GLBITMAP *glbmp)
{
	if ( glbmp ) {
		if ( glbmp->buf ) free(glbmp->buf);
		free(glbmp);
	}
}


GLuint loadtexture(const char *filename)  
{  
    GLuint tex = 0;  
    int tmp_bit;  
    int i;  
    int w, h;  
    int bpp;  
    unsigned char *bits = NULL;  
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;  
    FIBITMAP *bitmap = NULL;  
    GLBITMAP *glbmp = NULL;  
  
    fif = FreeImage_GetFileType(filename, 0);  
    if ( FIF_UNKNOWN == fif ) {  
        fif = FreeImage_GetFIFFromFilename(filename);  
        if ( FIF_UNKNOWN == fif )  
            return 0;     
    }  
    if ( FreeImage_FIFSupportsReading(fif) )   
        bitmap = FreeImage_Load(fif, filename, 0);  
      
    if ( !bitmap )   
        return 0;  

	int bitsPerPixel =  FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap32;
    if (bitsPerPixel == 32)
    {
        bitmap32 = bitmap;
    }
    else
    {
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    }
  
    glbmp = FIBitmap2GLBitmap(bitmap32);  
    if ( !glbmp )  
        return 0;  
  
    glGenTextures(1, &tex);  
    glBindTexture(GL_TEXTURE_2D, tex);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D, 0, glbmp->rgb_mode, glbmp->w, glbmp->h, 0, glbmp->rgb_mode, GL_UNSIGNED_BYTE, glbmp->buf);  
      
    FreeGLBitmap(glbmp);  
    FreeImage_Unload(bitmap32);
	if (bitsPerPixel != 32)
    {
        FreeImage_Unload(bitmap);
    }
  
    return tex;  
}  

}
}