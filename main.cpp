#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>

#include "altimap.hpp"
#include "entity.hpp"

#define HINC 10 //5 // Increment de hauteur
#define TSIZE 150 // Taille d'un dalle

#define MAPSIZE 50

#define t(a,b,c)  "( " << round(a) << " " << round(b) << " " << round(c) << " ) "

#define FACE_BOTTOM 1
#define FACE_FRONT 2
#define FACE_RIGHT 4
#define FACE_REAR 8
#define FACE_LEFT 16
#define FACE_UP 32

#define TEXTURE_SKIP (-2)
#define TEXTURE_CAULK (-1)
#define TEXTURE_HINT 9
#define TEXTURE_DIRT 3
#define TEXTURE_ROCK 4
#define TEXTURE_WATER 10 

#define WALL_ALL (FACE_UP+FACE_BOTTOM+FACE_RIGHT+FACE_LEFT+FACE_REAR+FACE_FRONT)
#define FACE_ALL (FACE_UP+FACE_BOTTOM+FACE_RIGHT+FACE_LEFT+FACE_REAR+FACE_FRONT)

#define rad(x) (x*M_PI/180)
#define deg(x) (x*180/M_PI)

#define maxabs(x,y,z) ((abs(x)>abs(y)?(abs(x)>abs(z)?x:z):(abs(y)>abs(z)?y:z)))

#define random() ((double)rand()/RAND_MAX)

using namespace std;

typedef struct _Entities_group{
	Entities aliens;
	Entities humans;
	Entities infos;
}Entities_group;

int textZ(double z)
{

	if(abs(z)< 70) //(255*HINC*0.2))
	{
		return TEXTURE_DIRT;
	}else{
		return TEXTURE_ROCK;
	}
}


string getTexture(int i){
	switch(i){
		case 1:
			return "example2/skybox 0 0 0 0.5 0.5 0 0 0";
		case 2:case TEXTURE_CAULK:
			return "common/caulk 0 0 0 0 0 0 0 0";
		case TEXTURE_HINT:
			return "common/hint 0 0 0 0 0 0 0 0";
		case TEXTURE_SKIP: //dans trem c'est toujours hint
			return "common/hint 0 0 0 0 0 0 0 0";
		case TEXTURE_DIRT:
			return "arkadia/eq2_rock_02 0 0 0 0 0 0 0 0";
		case TEXTURE_ROCK:
			return "arkadia/rock_1 0 0 0 0 0 0 0 0";
		case TEXTURE_WATER:
			return "example2/water 0 0 0 0.0 0.0 0 0 0";
		default:
			return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
			//return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
	}
}

/*string makeFace(double x, double y, double z, double tx, double ty, double tz, int texture){
  stringstream ret;

  ret << t(x+tx,y+ty,z+tz) << t(x+tx,y,z+tz) << t(x,y+ty,z+tz) << getTexture(texture) << endl; // iso-z
  ret << t(x+tx,y+ty,z+tz) << t(x,y+ty,z+tz) << t(x+tx,y+ty,z) << getTexture(texture) << endl; // iso-y
  ret << t(x+tx,y+ty,z+tz) << t(x+tx,y+ty,z) << t(x+tx,y,z+tz) << getTexture(texture) << endl; // iso-x

  ret << t(x,y,z) << t(x+tx,y,z) << t(x,y+ty,z) << getTexture(texture) << endl; // iso-z
  ret << t(x,y,z) << t(x,y,z+tz) << t(x+tx,y,z) << getTexture(texture) << endl; // iso-y
  ret << t(x,y,z) << t(x,y+ty,z) << t(x,y,z+tz) << getTexture(texture) << endl; // iso-x
  return ret.str();
  }
  */

string makeFace(double x, double y, double z, double tx, double ty, double tz, double ax , double ay, double az, int texture, int face){
	stringstream ret;
	double  dz=tx*tan(rad(az));
	double  dy=tx*tan(rad(ay));
	double  dx=ty*tan(rad(ax));


	//tx=abs(tx);
	//ty=abs(ty);
	//tz=abs(tz);
	int tdef=(texture==TEXTURE_HINT?TEXTURE_SKIP:TEXTURE_CAULK);

	//        ret << "// "<< x<<" "<<y<<" "<<z<<" "<<tx<<" "<<ty<<" "<< tz << " "<<ax<<" "<<ay<<" "<<az<<" "<< texture<<" " << face << endl;
	ret << "{" << endl;

	ret << t(x+tx-dx,y+ty+dy,z+tz+dz) << t(x+tx,y+dy,z+tz+dz) << t(x-dx,y+ty,z+tz) << getTexture((face == FACE_UP ? texture: tdef)) << 
		endl; // iso-z
	ret << t(x+tx-dx,y+ty+dy,z+tz) << t(x-dx,y+ty,z+tz) << t(x+tx-dx,y+ty+dy,z) << getTexture((face == FACE_REAR ? texture: tdef)) << endl; // iso-y
	ret << t(x+tx-dx,y+ty+dy,z+tz) << t(x+tx-dx,y+ty+dy,z) << t(x+tx,y+dy,z+tz) << getTexture((face == FACE_RIGHT ? texture: tdef)) << endl; // iso-x

	ret << t(x,y,z) << t(x+tx,y+dy,z+dz) << t(x-dx,y+ty,z) << getTexture((face == FACE_BOTTOM ? texture: tdef)) << endl; // iso-z
	ret << t(x,y,z) << t(x,y,z+tz) << t(x+tx,y+dy,z) << getTexture((face == FACE_FRONT ? texture: tdef)) << endl; // iso-y
	ret << t(x,y,z) << t(x-dx,y+ty,z) << t(x,y,z+tz) << getTexture((face == FACE_LEFT ? texture: tdef)) << endl; // iso-x
	ret << "}" << endl;
	return ret.str();
}

string getHeader(int xsize, int ysize){
	stringstream ret;
	ret << "//entity 0\n";
	ret << "{\n\"classname\" \"worldspawn\"\n";
	//	ret << "\"_blocksize\" \"16384 16384 16384\"\n"; //useless
	ret << "\"message\" \"map from heightmap " << xsize << "x" << ysize << "\"\n";

	return ret.str();
}

string getFoot(Entities_group * egp){
	stringstream ret;

	ret << "\n}\n";

	ret << egp->aliens.entitiesDump();
	ret << egp->humans.entitiesDump();
	ret << egp->infos.entitiesDump();

	return ret.str();
}

string makeTile(AltitudeMap * hmap, int xx, int yy, double z, double tx, double ty, double itz){
	stringstream ret;

	int w = hmap->xsize;
	int h = hmap->ysize;
	double x=xx*tx;
	double y=yy*ty;
	double tz=itz*hmap->getaltitude(xx,yy)*255+20;

	if((xx+1) < w && (yy+1) < h){
		double da=(itz*hmap->getaltitude(xx+1,yy)*255+20)-tz;
		double db=(itz*hmap->getaltitude(xx,yy+1)*255+20)-tz;
		double dc=(itz*hmap->getaltitude(xx+1,yy+1)*255+20)-tz;
		double ds = min(0.0,min(da,min(db,dc)));

		ret << "//c " << xx << " " << yy << "\n{\n";
		if(da==db && da == dc && da == 0 )
			ret << "// null " << endl;


		if( (da+db)/2.0 < (dc/2.0 +0.3)){ // condition de concavite

			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(textZ(maxabs(da,db,dc))) << endl; // iso-z
			ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(2) << endl; // iso-y
			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; // iso-x

			ret << t(x+tx,y+ty,z+tz+dc-10) << t(x,y+ty,z+tz+db-10) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; 
			ret << "}\n";

			ret << "{\n";
			ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(textZ(maxabs(da,db,dc))) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; 

			ret << t(x,y,z+tz-10) << t(x+tx,y,z+tz+da-10) << t(x,y+ty,z+tz+db-10) << getTexture(2) << endl; // iso-z
			ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+da+tz-10) << getTexture(2) << endl; // iso-y
			ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(2) << endl; // iso-x
			ret << "}\n";

		}else{ if(dc - da !=db ){


			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(textZ(maxabs(da,db,dc))) << endl; // iso-z
		}
		else{

			ret << "//pave" << endl;
		}
		ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(textZ(maxabs(da,db,dc))) << endl; // iso-z
		ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(2) << endl; // iso-y
		ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; // iso-x

		//carre 
		ret << t(x,y,z+tz+ds-10) << t(x+tx,y,z+tz+ds-10) << t(x,y+ty,z+tz+ds-10) << getTexture(2) << endl; // iso-z

		ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; // iso-y
		ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(2) << endl; // iso-x
		ret  <<  "}\n";

		}
	}
	return ret.str();
}

string makeSkybox(AltitudeMap * hmap, int sh){
	stringstream ret;

	double s = TSIZE;
	int w = hmap->xsize;
	int h = hmap->ysize;
	double max = (hmap->getmaxalt() +0.5) * 255 + 160 / sh; //bootstrap pour lan

	ret  << makeFace(-3,0,0,10,(h-1)*s+5,max*sh,0,0,0,1,FACE_RIGHT) << endl;
	ret  << makeFace(0,-3,0,(w-1)*s+5,10,max*sh,0,0,0,1,FACE_REAR) << endl;

	ret  << makeFace((w-1)*s-10+5,0,0,10,(h-1)*s+5,max*sh,0,0,0,1,FACE_LEFT) << endl;
	ret  << makeFace(0,(h-1)*s-5,0,(w-1)*s+5,10,max*sh,0,0,0,1,FACE_FRONT) << endl;

	ret  << makeFace(-3,-3,sh*max-10,(w-1)*s+5,(h-1)*s+5,16,0,0,0,1,FACE_BOTTOM) << endl;
	ret  << makeFace(-3,-3,sh*hmap->getmaxalt()*255,(w-1)*s+5,(h-1)*s+5,16,0,0,0,TEXTURE_HINT,FACE_BOTTOM) << endl;

	for(double i=1;i<(w-1)*s;i++){

		if((int)round(i)%500==0)
		{
			ret << 	makeFace(i,-3,0,10,(h-1)*s+5,max*sh,0,0,0,TEXTURE_HINT,FACE_RIGHT) << endl;
		}

	}

	for(double i=1;i<(h-1)*s;i++){

		if((int)round(i)%500==0)
		{
			ret <<	makeFace(0,i,0,(w-1)*s+5,10,max*sh,0,0,0,TEXTURE_HINT,FACE_FRONT) << endl;
		}

	}

	return ret.str();
}

string makeWater(AltitudeMap * hmap){
	
}

string makeGrid(AltitudeMap * hmap, int sh){
	stringstream ret;
	int i,j;
	int w = hmap->xsize;
	int h = hmap->ysize;

	for(j=0; j < (h-1); j++)
		for(i=0; i < (w-1); i++)
			ret << endl << makeTile(hmap,i,j,30,TSIZE,TSIZE,HINC) << endl;
	return ret.str();
}

void makeBasicEntities(AltitudeMap * hmap, Entities_group * egp){
        double max = hmap->getmaxalt() * 255 + 50 / HINC;

        double w = (MAPSIZE-1)*TSIZE;
        double h = (MAPSIZE-1)*TSIZE;

        egp->infos.entityAdd(Entity("info_alien_intermission",200,200,max*HINC,8.33));
        egp->infos.entityAdd(Entity("info_human_intermission",w-200,h-200,max*HINC,180));
        egp->infos.entityAdd(Entity("info_player_intermission",w/2.0,h/2.0,max*HINC));


        egp->humans.entityAdd(Entity("team_human_spawn",w-100,h-200,max*HINC));
        egp->humans.entityAdd(Entity("team_human_mgturret",w-200,h-200,max*HINC));
        egp->humans.entityAdd(Entity("team_human_reactor",w-100,h-100,max*HINC));
        egp->humans.entityAdd(Entity("team_human_armoury",w-200,h-100,max*HINC));


	egp->aliens.entityAdd(Entity("team_alien_spawn",150,300,max*HINC));
	egp->aliens.entityAdd(Entity("team_alien_overmind",150,150,max*HINC));
	egp->aliens.entityAdd(Entity("team_alien_acid_tube",300,300,max*HINC));
	egp->aliens.entityAdd(Entity("team_alien_acid_tube",240,240,max*HINC));
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

	makeBasicEntities(&hmap,&egp);

	cout << getHeader(MAPSIZE,MAPSIZE);
	cout << makeSkybox(&hmap,HINC);
	cout << makeGrid(&hmap,HINC);
	cout << getFoot(&egp);

	return 0;
}

