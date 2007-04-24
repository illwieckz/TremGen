#ifndef _HAVE_TEXTURES_H
#define _HAVE_TEXTURES_H

#define FACE_BOTTOM 1
#define FACE_FRONT 2
#define FACE_RIGHT 4
#define FACE_REAR 8
#define FACE_LEFT 16
#define FACE_UP 32

// definition des constantes des texutres

#define TEXTURE_SKYBOX (-10)
#define TEXTURE_ALPHA_100 (-13)
#define TEXTURE_ALPHA_50 (-12)
#define TEXTURE_ALPHA_0 (-11)
#define TEXTURE_WATER_CAULK (-3)
#define TEXTURE_SKIP (-2)
#define TEXTURE_CAULK (-1)
#define TEXTURE_HINT 81

#define TEXTURE_TER1 1
#define TEXTURE_TER2 2
#define TEXTURE_TER3 4
#define TEXTURE_TER4 8

#define TEXTURE_WATER 80 

string getTexture(int);

#endif // TEXTURES_H 
