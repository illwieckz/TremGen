#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>

#include "altimap.hpp"


#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define NORM "\033[0m"

#define CENTER 1 
#define TWATER 6 
#define TOP 2
#define BOTTOM 3
#define RIGHT 4
#define LEFT 5


#define WATERL 2 
#define WATER(x,y) (water[(x)*ysize+(y)])

typedef struct tagVECTOR2D{
        int x, y;
}VECTOR2D;

typedef struct tagCUBE{
	VECTOR2D lt;
	VECTOR2D rt;
	VECTOR2D lb;
	VECTOR2D rb;
	char modflag;
	char borderflag;
}CUBE;

std::ostream& operator<< (std::ostream& out, CUBE c)
{
        out << "(" << c.lt.x << "," << c.lt.y << ")";
        out << " " ;
        out << "(" << c.rt.x << "," << c.rt.y << ")";
        out << " " ;
        out << "(" << c.lb.x << "," << c.lb.y << ")";
        out << " " ;
        out << "(" << c.rb.x << "," << c.rb.y << ")";
        return out ;
}


CUBE markAsWater(AltitudeMap * hmap, char * water, int x, int y, int from, int level, double max, CUBE mvect){
	int xsize = hmap->xsize;
	int ysize = hmap->ysize;

	int alt = (int) (hmap->getaltitude(x,y)*10/max);
	alt = alt < 9 ? alt:9;

	if(from == CENTER){
		mvect.lt.x = xsize + 1;
		mvect.lt.y = ysize + 1;

		mvect.lb.x = xsize + 1;
		mvect.lb.y = 0;

		mvect.rt.x = 0;
                mvect.rt.y = ysize + 1;

		mvect.rb.x = 0;
		mvect.rb.y = 0;
		
		mvect.modflag = 0;
		mvect.borderflag = 0;
	}

	if(WATER(x,y) > 0 || (alt > (level + WATERL))){
		int a,b;
		a = b = 1;
		if((x == 0) || (x == xsize - 1)){
			mvect.borderflag = 1;
			a = 0;
		}
		if((y == 0) || (y == ysize - 1)){
			mvect.borderflag = 1;
			b = 0;
		}
		
		if(x < mvect.lt.x)
			mvect.lt.x = x + a;
		if(y < mvect.lt.y)
			mvect.lt.y = y + b;
		
		if(x > mvect.rb.x)
			mvect.rb.x = x - a;
		if(y > mvect.rb.y)
			mvect.rb.y = y - b;

		if(x < mvect.lb.x)
                        mvect.lb.x = x + a;
                if(y > mvect.lb.y)
                        mvect.lb.y = y - b;

		if(x > mvect.rt.x)
                        mvect.rt.x = x - a;
                if(y < mvect.rt.y)
                        mvect.rt.y = y + b;

		if(from != CENTER)
			mvect.modflag = 1;

		return mvect;
	}

	if(from == CENTER)
		WATER(x,y) = CENTER;
	else
		WATER(x,y) = TWATER;

	if(x > 0 && from != LEFT)
		mvect = markAsWater(hmap,water,x-1,y,RIGHT,level,max,mvect);
	if(y > 0 && from != TOP)
		mvect = markAsWater(hmap,water,x,y-1,BOTTOM,level,max,mvect);
	if(x < xsize - 1 && from != RIGHT)
		mvect = markAsWater(hmap,water,x+1,y,LEFT,level,max,mvect);
	if(y < ysize - 1 && from != BOTTOM)
		mvect = markAsWater(hmap,water,x,y+1,TOP,level,max, mvect);
		
	return mvect;
}

CUBE markAsWater(AltitudeMap * hmap, char * water, int x, int y, int level){
	double max = hmap->getmaxalt();
	//int xsize = hmap->xsize;
	int ysize = hmap->ysize;
	CUBE mvect;

	mvect = markAsWater(&(*hmap),water,x,y,CENTER,level,max,mvect);

	if(mvect.modflag == 1){
			WATER(mvect.lt.x,mvect.lt.y) = TOP;
			WATER(mvect.rt.x,mvect.rt.y) = RIGHT;
			WATER(mvect.lb.x,mvect.lb.y) = LEFT;
			WATER(mvect.rb.x,mvect.rb.y) = BOTTOM;
	}

	return mvect;
}

int main(){
	AltitudeMap hmap(50,50);

	hmap.randomize(0.5);
	hmap.subdivision(0.85,random(),random(),random(),random());
	hmap.randomize(0.2);
	hmap.erosion(2,1);
	hmap.normalize();

	int xsize = hmap.xsize;
	int ysize = hmap.ysize;

	int xcrop = xsize*10/100;
	int ycrop = ysize*10/100;
	double max = hmap.getmaxalt();
	int min = 10;
	
	CUBE mvect;
	
	char * water = new char[xsize*ysize];
	for(int x=0;x<xsize;x++)
		for(int y=0;y<ysize;y++)
			WATER(x,y) = 0;

	for(int x=xcrop; x < xsize - (xcrop/2); ++x){
		for(int y=ycrop; y < ysize - (ycrop/2); ++y){
			int alt = (int) (hmap.getaltitude(x,y)*10/max);
			alt = alt < 9 ? alt:9;
			if(alt < min)
				min = alt;
		} 
	}

	for(int x=xcrop; x < xsize - (xcrop/2); ++x){
		for(int y=ycrop; y < ysize - (ycrop/2); ++y){
			int alt = (int) (hmap.getaltitude(x,y)*10/max);
			alt = alt < 9 ? alt:9;
			if(alt == min){
				mvect = markAsWater(&hmap,water,x,y,alt);
				if(mvect.modflag == 1){
					double minalt = 1.0;
					double lalt;
					/*
					double a = hmap.getaltitude(mvect.lt.x,mvect.lt.y);
                                        double b = hmap.getaltitude(mvect.rt.x,mvect.rt.y);
                                        double c = hmap.getaltitude(mvect.lb.x,mvect.lb.y);
                                        double d = hmap.getaltitude(mvect.rb.x,mvect.rb.y);
                                        if(a < b && a < c && a < d)
                                                minalt = a;
                                        else if(b < a && b < c && b < d)
                                                minalt = b;
                                        else if(c < b && c < a && c < d)
                                                minalt = c;
                                        else if(d < c && d < b && d < a)
                                                minalt = d;

					printf("%g %g %g %g => %g\n",a,b,c,d,minalt);
					*/
					for(int j=mvect.lt.x; j < mvect.rt.x + 1; j++){
						lalt = hmap.getaltitude(j,mvect.lt.y);
						if(lalt < minalt)
							minalt = lalt;
						lalt = hmap.getaltitude(j,mvect.lb.y);
                                                if(lalt < minalt)
                                                        minalt = lalt;
					}
					for(int j=mvect.lt.y; j < mvect.lb.y + 1; j++){
						lalt = hmap.getaltitude(mvect.lt.x,j);
						if(lalt < minalt)
							minalt = lalt;
						lalt = hmap.getaltitude(mvect.rt.x,j);
                                                if(lalt < minalt)
                                                        minalt = lalt;
					}
					printf("minalt: %g\n",lalt);
					cout << mvect << endl;
				}
			}
		} 
	}

	for(int y=0; y < ysize; ++y){
		printf("%2d ",y);
		for(int x=0; x < xsize; ++x){
			int alt = (int) (hmap.getaltitude(x,y)*10/max);
			alt = alt < 9 ? alt:9;

			switch(WATER(x,y)){
				case CENTER:
					printf(RED"%d"NORM,alt);
					break;
				case TWATER:
					printf(BLUE"%d"NORM,alt);
					break;
				case TOP:
				case BOTTOM:
				case LEFT:
				case RIGHT:
					printf(GREEN"%d"NORM,alt);
					break;
				default:
					printf("%d",alt);
			}
		}
		printf("\n");
	}
	delete [] water;
}
