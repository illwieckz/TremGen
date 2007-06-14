#include "main.h"

#include "envgen.h"
#include "meshes.h"

string makeSkybox(AltitudeMap * hmap, int sh){
	stringstream ret;

	double s = TSIZE;
	int w = hmap->xsize;
	int h = hmap->ysize;
	double max = (hmap->getmaxalt() ) * 255 + 160 / sh; //+0.5 (dans axalt)bon bootstrap pour lan

	ret  << makeFace(-3,0,0,10,(h-1)*s+5,max*sh,0,0,0,TEXTURE_SKYBOX,FACE_RIGHT) << endl;
	ret  << makeFace(0,-3,0,(w-1)*s+5,10,max*sh,0,0,0,TEXTURE_SKYBOX,FACE_REAR) << endl;

	ret  << makeFace((w-1)*s-10+5,0,0,10,(h-1)*s+5,max*sh,0,0,0,TEXTURE_SKYBOX,FACE_LEFT) << endl;
	ret  << makeFace(0,(h-1)*s-5,0,(w-1)*s+5,10,max*sh,0,0,0,TEXTURE_SKYBOX,FACE_FRONT) << endl;

	ret  << makeFace(-3,-3,sh*max-10,(w-1)*s+5,(h-1)*s+5,16,0,0,0,TEXTURE_SKYBOX,FACE_BOTTOM) << endl;

	/*Embalage caulk*/

	ret  << makeFace(-13,-10,-10,10,(h-1)*s+5+20,max*sh+20,0,0,0,TEXTURE_CAULK,FACE_RIGHT) << endl;
	ret  << makeFace(-10,-13,-10,(w-1)*s+5+20,10,max*sh+20,0,0,0,TEXTURE_CAULK,FACE_REAR) << endl;

	ret  << makeFace((w-1)*s-10+5+10,-10,-10,10,(h-1)*s+5+20,max*sh+20,0,0,0,TEXTURE_CAULK,FACE_LEFT) << endl;
	ret  << makeFace(-10,(h-1)*s-5+10,-10,(w-1)*s+5+20,10,max*sh+20,0,0,0,TEXTURE_SKYBOX,FACE_FRONT) << endl;

	ret  << makeFace(-13,-13,sh*max-10+10,(w-1)*s+5+20,(h-1)*s+5+20,16,0,0,0,TEXTURE_CAULK,FACE_BOTTOM) << endl;
	ret  << makeFace(-13,-13,-10,(w-1)*s+5+20,(h-1)*s+5+20,16,0,0,0,TEXTURE_CAULK,FACE_BOTTOM) << endl;




	/*Embalage caulk*/
	/*
	   ret  << makeFace(-3,-3,sh*hmap->getmaxalt()*255,(w-1)*s+5,(h-1)*s+5,16,0,0,0,TEXTURE_HINT,FACE_BOTTOM) << endl;
	   *//*
	for(double i=1;i<(w-1)*s;i++){

		if((int)round(i)%500==0)
		{
			ret << 	makeFace(i,-3,0,10,(h-1)*s+5,max*sh-160,0,0,0,TEXTURE_HINT,FACE_RIGHT) << endl;
		}

	}

	for(double i=1;i<(h-1)*s;i++){

		if((int)round(i)%500==0)
		{
			ret <<	makeFace(0,i,0,(w-1)*s+5,10,max*sh-160,0,0,0,TEXTURE_HINT,FACE_FRONT) << endl;
		}

	} */
	for(double i=10+hmap->getminalt()*255;i<max;i+=40){
		//fprintf(stderr,"%f %f\n",i,max);
		ret  << makeFace(-3,-3,i*sh,(w-1)*s+5,(h-1)*s+5,16,0,0,0,TEXTURE_HINT,FACE_BOTTOM) << endl;
	}
	return ret.str();
}

WATERCUBE markAsWater(AltitudeMap * hmap, int x, int y, int from, int level, double max, WATERCUBE mvect){
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

		mvect.depth = 1;

		mvect.modflag = 0;
	}

	if(mvect.depth > hmap->getaltitude(x,y))
		mvect.depth = hmap->getaltitude(x,y);

	if(hmap->getwater(x,y) > 0 || (alt > (level + WATERL))){
		int a,b; a = b = 1;

		if((x == 0) || (x == xsize - 1))
			a = 0;
		if((y == 0) || (y == ysize - 1))
			b = 0;

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
		hmap->setwater(x,y,CENTER);
	else
		hmap->setwater(x,y,TWATER);

	if(x > 0 && from != LEFT)
		mvect = markAsWater(hmap,x-1,y,RIGHT,level,max,mvect);
	if(y > 0 && from != TOP)
		mvect = markAsWater(hmap,x,y-1,BOTTOM,level,max,mvect);
	if(x < xsize - 1 && from != RIGHT)
		mvect = markAsWater(hmap,x+1,y,LEFT,level,max,mvect);
	if(y < ysize - 1 && from != BOTTOM)
		mvect = markAsWater(hmap,x,y+1,TOP,level,max, mvect);

	return mvect;
}

WATERCUBE markAsWater(AltitudeMap * hmap, int x, int y, int level){
	double max = hmap->getmaxalt();
	WATERCUBE mvect;

	return markAsWater(&(*hmap),x,y,CENTER,level,max,mvect);
}

string makeWater(AltitudeMap * hmap, int sh){
	stringstream ret;

	double s = TSIZE;
	sh=sh*255;
	int xsize = hmap->xsize;
	int ysize = hmap->ysize;

	int xcrop = xsize*10/100;
	int ycrop = ysize*10/100;
	double vmax = hmap->getmaxalt();
	int min = 10;

	WATERCUBE mvect;

	for(int x=xcrop; x < xsize - (xcrop/2); ++x){
		for(int y=ycrop; y < ysize - (ycrop/2); ++y){
			int alt = (int) (hmap->getaltitude(x,y)*10/vmax);
			alt = alt < 9 ? alt:9; 
			if(alt < min)
				min = alt;
		}
	}

	for(int x=xcrop; x < xsize - (xcrop/2); ++x){
		for(int y=ycrop; y < ysize - (ycrop/2); ++y){
			int alt = (int) (hmap->getaltitude(x,y)*10/vmax);
			alt = alt < 9 ? alt:9;
			if(alt == min){
				mvect = markAsWater(&(*hmap),x,y,alt);
				if(mvect.modflag == 1){
					double minalt=1.0;
					double lalt;

					for(int j=mvect.lt.x; j < mvect.rt.x + 1; j++){
						lalt = hmap->getaltitude(j,mvect.lt.y);
						if(lalt < minalt)
							minalt = lalt;
						lalt = hmap->getaltitude(j,mvect.lb.y);
						if(lalt < minalt)
							minalt = lalt;
					}

					for(int j=mvect.lt.y; j < mvect.lb.y + 1; j++){
						lalt = hmap->getaltitude(mvect.lt.x,j);
						if(lalt < minalt)
							minalt = lalt;
						lalt = hmap->getaltitude(mvect.rt.x,j);
						if(lalt < minalt)
							minalt = lalt;
					}

					hmap->setwater(mvect.lt.x,mvect.lt.y,TOP);
					hmap->setwater(mvect.rt.x,mvect.rt.y,RIGHT);
					hmap->setwater(mvect.lb.x,mvect.lb.y,LEFT);
					hmap->setwater(mvect.rb.x,mvect.rb.y,BOTTOM);
#ifdef DEBUG
					fprintf(stderr,"DEBUG: Water Positions: \n (%d,%d,%g) (%d,%d,%g) (%d,%d,%g) (%d,%d,%g) | Depth: %g\n",mvect.lt.x,mvect.lt.y,minalt,mvect.rt.x,mvect.rt.y,minalt,mvect.lb.x,mvect.lb.y,minalt,mvect.rb.x,mvect.rb.y,minalt,minalt - mvect.depth);
#endif
					ret  << makeFace(mvect.rb.x*s,mvect.rb.y*s,mvect.depth*sh,(mvect.lt.x-mvect.rb.x)*s,(mvect.rt.y-mvect.lb.y)*s,(minalt - mvect.depth)*sh,0,0,0,TEXTURE_WATER,FACE_UP) << endl;
					// fog of war
					//ret  << makeFace(mvect.rb.x*s,mvect.rb.y*s,mvect.depth*sh,(mvect.lt.x-mvect.rb.x)*s,(mvect.rt.y-mvect.lb.y)*s,(minalt - mvect.depth)*sh,0,0,0,TEXTURE_WATER,FACE_UP) << endl;
				}
			}
		}
	}

	for(int y=0; y < ysize; ++y){
		fprintf(stderr,"%2d ",y);
		for(int x=0; x < xsize; ++x){
			int alt = (int) (hmap->getaltitude(x,y)*10/vmax);
			alt = alt < 9 ? alt:9;
			switch(hmap->getwater(x,y)){
				case CENTER:
					fprintf(stderr,RED"%d"NORM,alt);
					break;
				case TWATER:
					fprintf(stderr,BLUE"%d"NORM,alt);
					break;
				case TOP:
				case BOTTOM:
				case LEFT:
				case RIGHT:
					fprintf(stderr,GREEN"%d"NORM,alt);
					break;
				default:
					fprintf(stderr,"%d",alt);
			}

		}
		fprintf(stderr,"\n");
	}

	return ret.str();
}

string makeGrid(AltitudeMap * hmap, int sh){
	stringstream ret;
	int i,j;
	int w = hmap->xsize;
	int h = hmap->ysize;

	for(j=0; j < (h-1); j++)
		for(i=0; i < (w-1); i++){
			ret << endl << makeTile(hmap,i,j,30,TSIZE,TSIZE,HINC) << endl;
			if(hmap->gettex(i,j)!= hmap->gettex(i,j+1)  || hmap->gettex(i+1,j)!= hmap->gettex(i,j)) {
				double x=i*TSIZE;
				double y=j*TSIZE;
				double tx,ty;
				tx=ty=TSIZE;

				ret << endl << makeFace(x+tx/2-10,y+ty/2-10,HINC*255*(hmap->getaltitude(i,j)+hmap->getaltitude(i+1,j+1))/2.0-20,20,20,100,0,0,0,TEXTURE_ALPHA_0,FACE_ALL) << endl ;
				//ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+150,10,10,10,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;

			}	
			if(hmap->gettex(i,j)!= hmap->gettex(i,j+1) )
			{
				double x=i*TSIZE;
				double y=j*TSIZE;
				double tx,ty;
				tx=ty=TSIZE;

				//ret << endl << makeFace(x+tx-10,y,HINC*255*(hmap->getaltitude(i,j+1)+hmap->getaltitude(i+1,j+1))/2.0-20,20,100,100,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;

				ret << endl << makeFace(x+tx/2,y+ty-10,HINC*255*(hmap->getaltitude(i+1,j)+hmap->getaltitude(i+1,j+1))/2+20,20,20,100,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
				//ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+150,10,10,10,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
			}


			if(hmap->gettex(i+1,j)!= hmap->gettex(i,j) )
			{
				double x=i*TSIZE;
				double y=j*TSIZE;
				double tx,ty;
				tx=ty=TSIZE;

				ret << endl << makeFace(x+tx-10,y+ty/2,HINC*255*(hmap->getaltitude(i,j+1)+hmap->getaltitude(i+1,j+1))/2.0-20,20,20,100,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
				//ret << endl << makeFace(x,y+ty-10,HINC*255*(hmap->getaltitude(i+1,j)+hmap->getaltitude(i+1,j+1))/2+20,100,20,100,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;

				//ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+150,10,10,10,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
			}

			/*	
				if(hmap->gettex(i,j)!= hmap->gettex(i-1,j) )
				{
				double x=i*TSIZE;
				double y=j*TSIZE;
				double tx,ty;
				tx=ty=TSIZE;

				ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+30,10,10,10,0,0,0,TEXTURE_ALPHA_50,FACE_ALL) << endl ;
			//ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+150,10,10,10,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
			}



			if(hmap->gettex(i,j)!= hmap->gettex(i,-1) )
			{
			double x=i*TSIZE;
			double y=j*TSIZE;
			double tx,ty;
			tx=ty=TSIZE;

			ret << endl << makeFace(x,y+ty/2,HINC*255*hmap->getaltitude(i,j)+30,10,10,10,0,0,0,TEXTURE_ALPHA_50,FACE_ALL) << endl ;
			//ret << endl << makeFace(x+tx/2,y,HINC*255*hmap->getaltitude(i,j)+150,10,10,10,0,0,0,TEXTURE_ALPHA_100,FACE_ALL) << endl ;
			}



*/	

















		}
	return ret.str();
}

