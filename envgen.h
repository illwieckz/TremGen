#ifndef _HAVE_ENVGEN_H
#define _HAVE_ENVGEN_H

#include "altimap.h"

#define CENTER 1 
#define TWATER 6 
#define TOP 2
#define BOTTOM 3
#define RIGHT 4
#define LEFT 5

#define WALL_ALL (FACE_UP+FACE_BOTTOM+FACE_RIGHT+FACE_LEFT+FACE_REAR+FACE_FRONT)
#define FACE_ALL (FACE_UP+FACE_BOTTOM+FACE_RIGHT+FACE_LEFT+FACE_REAR+FACE_FRONT)

#define WATERL 2 // Variable qui definit la hauteur des lacs et leur etendu
//#define WATER(x,y) (water[(x)*ysize+(y)])

typedef struct tagWATERCUBE{
        VECTOR2D lt;
        VECTOR2D rt;
        VECTOR2D lb;
        VECTOR2D rb;

        double depth;
        char modflag;
}WATERCUBE;


/****/

string makeSkybox(AltitudeMap *, int);
WATERCUBE markAsWater(AltitudeMap *, int, int, int, int, double, WATERCUBE);
WATERCUBE markAsWater(AltitudeMap *, int, int, int);
string makeWater(AltitudeMap *, int);
string makeGrid(AltitudeMap *, int);

#endif // ENVGEN_H

