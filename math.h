#ifndef _HAVE_MATH_H
#define _HAVE_MATH_H

#define rad(x) (x*M_PI/180)
#define deg(x) (x*180/M_PI)
        
#define maxabs(x,y,z) ((abs(x)>abs(y)?(abs(x)>abs(z)?x:z):(abs(y)>abs(z)?y:z)))

#define random() ((double)rand()/RAND_MAX)
#define notinarena(lx,ly,lxx,lyy)  (hmap->getaltitude(lx,ly)==0 || lxx>=(hmap->xsize-2) || lyy>=(hmap->ysize-2) || lxx<=0 || lyy <= 0)
        
#define mdistance(x,y,X,Y) (sqrt((x-X)*(x-X)+(y-Y)*(y-Y)))

#endif // MATH_H
