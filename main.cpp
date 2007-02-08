#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>

#include "altimap.hpp"
//#include "entity.hpp"

#define HINC 5 // Increment de hauteur
#define TSIZE 100 // Taille d'un dalle

#define MAPSIZE 100

#define t(a,b,c)  "( " << round(a) << " " << round(b) << " " << round(c) << " ) "

using namespace std;

string getTexture(int i){
	switch(i){
		case 1:
			return "example2/skybox 0 0 0 0.5 0.5 0 0 0";
		case 2:
			return "common/caulk 0 0 0 0 0 0 0 0";
		default:
			return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
			//return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
	}
}

string makeEntity(string name, double x, double y, double z, double angle){
	stringstream ret;
	static int id=0;
	
	id++;

	ret << "// entity " << id << endl << "{" << endl; 
	ret << "\"classname\" \"" << name << "\"" << endl;
	ret << "\"origin\" \"" << x << " " << y << " " << z << "\"" << endl;
	if(angle != 0.0)
		ret << "\"angle\" \"" << angle << "\"" << endl;
	ret << "}" << endl;

	return ret.str();
}

string makeFace(double x, double y, double z, double tx, double ty, double tz, int texture){
	stringstream ret;

	ret << t(x+tx,y+ty,z+tz) << t(x+tx,y,z+tz) << t(x,y+ty,z+tz) << getTexture(texture) << endl; // iso-z
	ret << t(x+tx,y+ty,z+tz) << t(x,y+ty,z+tz) << t(x+tx,y+ty,z) << getTexture(texture) << endl; // iso-y
	ret << t(x+tx,y+ty,z+tz) << t(x+tx,y+ty,z) << t(x+tx,y,z+tz) << getTexture(texture) << endl; // iso-x

	ret << t(x,y,z) << t(x+tx,y,z) << t(x,y+ty,z) << getTexture(texture) << endl; // iso-z
	ret << t(x,y,z) << t(x,y,z+tz) << t(x+tx,y,z) << getTexture(texture) << endl; // iso-y
	ret << t(x,y,z) << t(x,y+ty,z) << t(x,y,z+tz) << getTexture(texture) << endl; // iso-x
	return ret.str();
}

string getHeader(int xsize, int ysize){
	stringstream ret;
	ret << "//entity 0\n";
	ret << "{\n\"classname\" \"worldspawn\"\n";
	ret << "\"_blocksize\" \"8192 8192 2048\"\n";
	ret << "\"message\" \"map from heightmap " << xsize << "x" << ysize << "\"\n";

	return ret.str();
}

string getFoot(AltitudeMap * hmap){
	stringstream ret;
	double max = hmap->getmaxalt() * 255 + 50 / HINC;

	ret << "\n}\n";
	ret << makeEntity("team_human_spawn",144,280,max*HINC,0);
	ret << makeEntity("team_alien_spawn",280,248,max*HINC,0);
	ret << makeEntity("info_alien_intermission",272,360,max*HINC,8.33);
	ret << makeEntity("info_human_intermission",1056,360,max*HINC,180);
	ret << makeEntity("info_player_intermission",424,944,max*HINC,0);
	return ret.str();
}

string makeTile(AltitudeMap * hmap, int xx, int yy, double z, double tx, double ty, double itz){
	stringstream ret;

	int w = hmap->getxsize();
	int h = hmap->getysize();
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

			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(0) << endl; // iso-z
			ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(2) << endl; // iso-y
			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; // iso-x

			ret << t(x+tx,y+ty,z+tz+dc-10) << t(x,y+ty,z+tz+db-10) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; 
			ret << "\n}\n";

			ret << "{\n";
			ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(0) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; 

			ret << t(x,y,z+tz-10) << t(x+tx,y,z+tz+da-10) << t(x,y+ty,z+tz+db-10) << getTexture(2) << endl; // iso-z
			ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+da+tz-10) << getTexture(2) << endl; // iso-y
			ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(2) << endl; // iso-x
			ret << "\n}\n";

		}else{ if(dc - da !=db ){


			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(0) << endl; // iso-z
			}
			else{
			
				ret << "//pave" << endl;
			}
			ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(0) << endl; // iso-z
			ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(2) << endl; // iso-y
			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(2) << endl; // iso-x

			//carre 
			ret << t(x,y,z+tz+ds-10) << t(x+tx,y,z+tz+ds-10) << t(x,y+ty,z+tz+ds-10) << getTexture(2) << endl; // iso-z

			ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+tz+da-10) << getTexture(2) << endl; // iso-y
			ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(2) << endl; // iso-x
			ret  <<  "\n}\n";

		}
	}
	return ret.str();
}

string makeSkybox(AltitudeMap * hmap, int sh){
	stringstream ret;

	double s = TSIZE;
	int w = hmap->getxsize();
	int h = hmap->getysize();
	double max = hmap->getmaxalt() * 255 + 160 / sh;

	ret << "{\n" << makeFace(-3,0,0,10,(h-1)*s+5,max*sh,1) << "\n}\n";
	ret << "{\n" << makeFace(0,-3,0,(w-1)*s+5,10,max*sh,1) << "\n}\n";

	ret << "{\n" << makeFace((w-1)*s-10+5,0,0,10,(h-1)*s+5,max*sh,1) << "\n}\n";
	ret << "{\n" << makeFace(0,(h-1)*s-5,0,(w-1)*s+5,10,max*sh,1) << "\n}\n";

	ret << "{\n" << makeFace(-3,-3,sh*max-10,(w-1)*s+5,(h-1)*s+5,16,1) << "\n}\n";

	return ret.str();
}

string makeGrid(AltitudeMap * hmap, int sh){
	stringstream ret;
	int i,j;
	int w = hmap->getxsize();
        int h = hmap->getysize();
	
	for(j=0; j < (h-1); j++)
		for(i=0; i < (w-1); i++)
			ret << endl << makeTile(hmap,i,j,30,TSIZE,TSIZE,HINC) << endl;
	return ret.str();
}


int main(int argc,char **argv)
{
	AltitudeMap hmap(MAPSIZE,MAPSIZE);

	//hmap.randomize(0.1);
        hmap.subdivision(0.85,0.4,0.4,0.2,0.1);
	
	hmap.erosion(2,1);
	hmap.normalize();
	
	cout << getHeader(MAPSIZE,MAPSIZE);
	cout << makeSkybox(&hmap,HINC);
	cout << makeGrid(&hmap,HINC);
	cout << getFoot(&hmap);

	return 0;
}

