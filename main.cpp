#include "main.h"
#include "textures.h"
#include "meshes.h"

#include "entity.h"

#include "math.h"

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

using namespace std;

typedef struct tagEntities_group{
	Entities aliens;
	Entities humans;
	Entities infos;

	Entities misc;
}Entities_group;

typedef struct tagVECTOR2D{
	int x, y;
}VECTOR2D;

typedef struct tagWATERCUBE{
	VECTOR2D lt;
	VECTOR2D rt;
	VECTOR2D lb;
	VECTOR2D rb;

	double depth;	
	char modflag;
}WATERCUBE; 

string getHeader(int xsize, int ysize){
	stringstream ret;
	ret << "//entity 0\n";
	ret << "{\n\"classname\" \"worldspawn\"\n";
	ret << "\"_blocksize\" \"16384 16384 16384\"\n"; //seemingly useless
	ret << "\"message\" \"map from heightmap " << xsize << "x" << ysize << "\"\n";

	return ret.str();
}

string getFoot(Entities_group * egp){
	stringstream ret;

	ret << "\n}\n";

	ret << egp->aliens.entitiesDump();
	ret << egp->humans.entitiesDump();
	ret << egp->infos.entitiesDump();
	ret << egp->misc.entitiesDump();

	return ret.str();
}


double getRealAlt(AltitudeMap * hmap ,double x, double y,double tx,double ty, double itz)
{

	//fprintf(stderr,"--%f %f\n",tx,ty);
	int xx=(int)floor(x/tx);
	int yy=(int)floor(y/ty);

	double tz=itz*hmap->getaltitude(xx,yy)*255+20; //hauteur de base
	double dx=x-xx*tx;
	dx/=tx;
	double dy=y-yy*ty; //rajout en %
	dy/=ty;
	//fprintf(stderr,"%f %f\n",dx,dy);
	double da=(itz*hmap->getaltitude(xx+1,yy)*255+20)-tz;
	double db=(itz*hmap->getaltitude(xx,yy+1)*255+20)-tz;
	double dc=(itz*hmap->getaltitude(xx+1,yy+1)*255+20)-tz;

	if(dy<dx)
	{//en bas


		return tz+(da*dx+db*dy);///2 ;
	}else{

		return tz+dc+((db-dc)*(1-dx)+(da-dc)*(1-dy));///2 ;
	}


	//if( (da+db)/2.0 < (dc/2.0 +0.3)){ // condition de concavite
	//cherchons la bonne diagonale
	/*
	 *  (db)----- (dc)
	 *	|\ /|
	 *	| X |
	 *	|/ \|
	 *	-----
	 *    1ere   2eme (da)
	 */
	/*	if( dc < da || dc < db) //1ere 
		{
		if(dy<dx){ //en bas

		return tz+(da*dx+(da-dc)*dy);///2;

		}else{
		return tz+((db-dc)*dx+db*dy);///2;;
		}

		}else{ //2eme

		if((1-dy)>dx ){//en bas

		return tz+(da*dx+db*dy);///2 ;
		}else{

		return tz+((dc-db)*(dx)+(da-dc)*(dy));///2 ;

		}

		}

		}else{
	//convexe :
	if(dc - da !=db ){ //si plat
	return tz+(da*dx+db*dy);///2 ;
	}


	if( dc > da || dc > db) //1ere 
	{

	if(dy<dx){ //en bas

	return tz+(da*dx+(dc-da)*dy);///2;

	}else{
	return tz+((dc-db)*dx+db*dy);///2;
	}
	}else{//deuxième

	if((1-dy)>dx ){//en bas

	return tz+(da*dx+db*dy);///2 ;
	}else{

	return tz+((dc-db)*(dx)+abs(dc-da)*(dy));///2 ;

	}

	}


	}
	//ça serait cool que ça marche
	*/
}

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

					fprintf(stderr,"DEBUG: Water Positions: \n (%d,%d,%g) (%d,%d,%g) (%d,%d,%g) (%d,%d,%g) | Depth: %g\n",mvect.lt.x,mvect.lt.y,minalt,mvect.rt.x,mvect.rt.y,minalt,mvect.lb.x,mvect.lb.y,minalt,mvect.rb.x,mvect.rb.y,minalt,minalt - mvect.depth);

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

void  plantForest(double cx, double cy, int numTree, AltitudeMap * hmap, Entities_group * egp)
{

	stringstream buf;
	Entity * etmp;
	double k;
	k=hmap->xsize+hmap->ysize;
	k/=2.0;
	k/=10;//1/10ème rayon de la foret
	bool flag=false;
	double phx,phy,pax,pay;
	phx=hmap->getHumanPosX()/TSIZE;
	phy=hmap->getHumanPosY()/TSIZE;
	pax=hmap->getAlienPosX()/TSIZE;
	pay=hmap->getAlienPosY()/TSIZE;


	for(int i=numTree; i > 0; i--){
		if(round(random()*100)>5 && !flag ){
			double r,theta,lxx,lyy;
			int lx,ly;
			int stop=1000;
			do{
				r=(-pow(random(),2)+1)*k;
				theta=round(random()*36000)/100.0;
				lxx=cx+r*cos(rad(theta));
				lyy=cy+r*sin(rad(theta));
				lx=(int)floor(lxx);
				ly=(int)floor(lyy);
				stop--;
				if(stop==0){ flag=true; 
					fprintf(stderr,"Bye Bye Forest!\n");
					break;}
					//fprintf(stderr,"))%f\n",mdistance(pax,pay,lxx,lyy));

			}while(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || hmap->getaltitude(lx,ly)==0 || lxx>=(hmap->xsize-2) || lyy>=(hmap->ysize-2) || lxx<=0 || lyy <= 0 || mdistance(pax,pay,lxx,lyy)<=1.5 || mdistance(phx,phy,lxx,lyy)<=1.5);
			if(flag){
				continue;
			}

			//fprintf(stderr,"%d %d %d\n",lx,ly,hmap->getwater(lx,ly));

			egp->misc.entityAdd(Entity("misc_model",lxx*TSIZE,lyy*TSIZE,real(lxx*TSIZE,lyy*TSIZE)-10));// -10 pour enfoncage dans sol 
			if((etmp = egp->misc.entityAt(-1)) != NULL){
				buf.str("");
				buf << "models/mapobjects/ctftree/ctftree" << round(random()*2+1) << ".md3";
				etmp->attrAdd("model",buf.str());
				etmp->attrAdd("spawnflags",2);
				etmp->attrAdd("modelscale",2.0+0.6*r/k);
				etmp->attrAdd("angle",round(random()*36000)/100.0);
			}
		}else{//changement de foret
			double ncx,ncy;
			ncx =  round((hmap->xsize-1)*random()*100)/100.0;
			ncy =  round((hmap->ysize-1)*random()*100)/100.0;
			int temp=i;
			if(!flag){
				temp/=2;
			}else{
				temp=0;
				flag = false;
			}
			plantForest(ncx,ncy,i-temp,hmap,egp);
			i=temp;
		}

	}

}


void  dropBox(AltitudeMap * hmap, Entities_group * egp){
	double ncx,ncy;
	int lx,ly;
	Entity * etmp;
	double phx,phy,pax,pay;

	phx=hmap->getHumanPosX()/TSIZE;
	phy=hmap->getHumanPosY()/TSIZE;                                                                                                              pax=hmap->getAlienPosX()/TSIZE;
	pay=hmap->getAlienPosY()/TSIZE;
	for(int i=0; i < NUMBOXES; i++){
		do{
			ncx =  round((hmap->xsize-1)*random()*100)/100.0;
			ncy =  round((hmap->ysize-1)*random()*100)/100.0;

			lx=(int)floor(ncx);
			ly=(int)floor(ncy);

			//}while(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || hmap->getaltitude(lx,ly)==0 || ncx>=(hmap->xsize-2) || ncy>=(hmap->ysize-2) || ncx<=0 || ncy <= 0 || mdistance(pax,pay,ncx,ncy)<=1.5 || mdistance(phx,phy,ncx,ncy)<=1.5);
	}while(hmap->getaltitude(lx,ly)==0 || ncx>=(hmap->xsize-2) || ncy>=(hmap->ysize-2) || ncx<=0 || ncy <= 0 || mdistance(pax,pay,ncx,ncy)<=1.5 || mdistance(phx,phy,ncx,ncy)<=1.5);

	egp->misc.entityAdd(Entity("misc_model",ncx*TSIZE,ncy*TSIZE,real(ncx*TSIZE,ncy*TSIZE)-60+random()*25));// -10 pour enfoncage dans sol 

	if((etmp = egp->misc.entityAt(-1)) != NULL){
		etmp->attrAdd("model","models/mapobjects/box.md3");
		etmp->attrAdd("spawnflags",2);
		etmp->attrAdd("modelscale",3);
		etmp->attrAdd("angle",round(random()*36000)/100.0);
	}
}
}

double mesureAlien(double x, double y,double max,AltitudeMap * hmap)
{

	double al=real(x,y);

	int lx=(int)floor(x);
	int ly=(int)floor(y);
	al+=hmap->getaltitude(lx-1,ly);
	al+=hmap->getaltitude(lx,ly-1);
	al+=hmap->getaltitude(lx+1,ly);
	al+=hmap->getaltitude(lx,ly+1);

	if(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || notinarena(lx,ly,x,y)) //dans l'eau ou hors map
		return 0;
	//fprintf(stderr,"--%f\n",al/(max*HINC));
	return 1-((al/5.0)/(max*HINC));
}


double mesureHuman(double x, double y,double dist,double max,AltitudeMap * hmap)
{

	double al=real(x,y);

	int lx=(int)floor(x);
	int ly=(int)floor(y);
	al+=hmap->getaltitude(lx-1,ly);
	al+=hmap->getaltitude(lx,ly-1);
	al+=hmap->getaltitude(lx+1,ly);
	al+=hmap->getaltitude(lx,ly+1);

	if(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || notinarena(lx,ly,x,y)) //dans l'eau ou hors map
		return 0;
	double moy=(hmap->xsize+hmap->ysize)/2.0;
	//fprintf(stderr,"--%f %f\n",moy,dist);
	return (((al/5.0)/(max*HINC))+dist/moy)/2.0; //we j'approx faudrait la diag et pas lamoyenne
}

void makeBasicEntities(AltitudeMap * hmap, Entities_group * egp){
	double max = hmap->getmaxalt() * 255 + 50 / HINC;


	double w = (MAPSIZE-2); /*Attention -2*/
	double h = (MAPSIZE-2);
	double px,py;
	egp->infos.entityAdd(Entity("info_player_intermission",w*TSIZE/2.0,h*TSIZE/2.0,max*HINC));

	float seuil=0.8;
	int stop=50;
	do
	{
		px=1+random()*w;
		py=1+random()*h;


		fprintf(stderr,"%f %f %f\n",px,py,mesureAlien(px,py,max,hmap));
		stop--;
		if(stop==0)
		{
			stop=50;
			seuil-=seuil/10;
			fprintf(stderr,"Descente seuil Alien : %f \n",seuil);
		}

	}while(mesureAlien(px,py,max,hmap)<seuil);

	px*=TSIZE;
	py*=TSIZE;

	hmap->setAlienPos(px,py);

	egp->infos.entityAdd(Entity("info_alien_intermission",px-110,py-110,real(px-100,py-100)+200,8.33));

	egp->aliens.entityAdd(Entity("team_alien_spawn",px+150,py-100,real(px-100,py+150)+150));
	egp->aliens.entityAdd(Entity("team_alien_overmind",px,py,real(px,py)+150));
	egp->aliens.entityAdd(Entity("team_alien_acid_tube",px+100,py+100,real(px+100,py+100)+150));
	egp->aliens.entityAdd(Entity("team_alien_acid_tube",px+140,py+140,real(px+140,py+140)+150));
	double tmp;

	seuil=0.8;
	stop=50;
	do
	{
		px=1+random()*w;
		py=1+random()*h;




		tmp=hmap->getHumanPosX()-px;
		tmp*=tmp;

		double tmp2=hmap->getHumanPosY()-py;
		tmp2*=tmp2;

		tmp+=tmp2;
		tmp=sqrt(tmp);

		fprintf(stderr,"%f %f %f\n",px,py,mesureHuman(px,py,tmp,max,hmap));
		stop--;
		if(stop==0)
		{
			stop=50;
			seuil-=seuil/10;
			fprintf(stderr,"Descente seuil Human : %f \n",seuil);
		}

	}while(mesureHuman(px,py,tmp,max,hmap)<seuil);

	px*=TSIZE;
	py*=TSIZE;

	hmap->setHumanPos(px,py);


	egp->infos.entityAdd(Entity("info_human_intermission",px,py,real(px,py)+200,180));

	egp->humans.entityAdd(Entity("team_human_spawn",px+150,py,real(px+150,py)+150));
	egp->humans.entityAdd(Entity("team_human_mgturret",px,py,real(px,py)+150));
	egp->humans.entityAdd(Entity("team_human_reactor",px+150,py+150,real(px+150,py+150)+150));
	egp->humans.entityAdd(Entity("team_human_armoury",px,py+150,real(px,py+150)+150));







	double cx,cy;
	cx=cy=(hmap->xsize-1)/4.0;
	cx +=  round((hmap->xsize-1)/2.0*random()*100)/100.0;
	cy +=  round((hmap->ysize-1)/2.0*random()*100)/100.0;

	plantForest(cx,cy,NUMTREES,hmap,egp);

	dropBox(hmap,egp);

}




int main(int argc,char **argv)
{
	Entities_group egp;	

	AltitudeMap hmap(MAPSIZE,MAPSIZE);

	hmap.randomize(0.5);
	hmap.subdivision(0.85,random(),random(),random(),random());
	hmap.randomize(0.2);
	hmap.erosion(2,1);
	hmap.normalize();

	cout << getHeader(MAPSIZE,MAPSIZE);
	cout << makeSkybox(&hmap,HINC);
	cout << makeGrid(&hmap,HINC);
	cout << makeWater(&hmap,HINC);

	makeBasicEntities(&hmap,&egp);

	cout << getFoot(&egp);

	return 0;
}

