#include "main.h"
#include "meshes.h"

#include "math.h"

#define t(a,b,c)  "( " << round(a) << " " << round(b) << " " << round(c) << " ) "

string makeFace(double x, double y, double z, double tx, double ty, double tz, double ax , double ay, double az, int texture, int face){
	stringstream ret;
	double  dz=tx*tan(rad(az));
	double  dy=tx*tan(rad(ay));
	double  dx=ty*tan(rad(ax));


	//tx=abs(tx);
	//ty=abs(ty);
	//tz=abs(tz);
	int tdef=0;

	//	(texture==TEXTURE_HINT?TEXTURE_SKIP:TEXTURE_CAULK);
	switch (texture)
	{
		case TEXTURE_HINT: /*Les autres faces des hint sont en skip*/
			tdef=TEXTURE_SKIP;
			break;

		case TEXTURE_WATER: /*Les autres faces des haut sont en water_caulk*/
			tdef=TEXTURE_WATER_CAULK;
			break;

		default: /* Par defaut caulk*/
			tdef=TEXTURE_CAULK;

	}



	//        ret << "// "<< x<<" "<<y<<" "<<z<<" "<<tx<<" "<<ty<<" "<< tz << " "<<ax<<" "<<ay<<" "<<az<<" "<< texture<<" " << face << endl;
	ret << "{" << endl;

	ret << t(x+tx-dx,y+ty+dy,z+tz+dz) << t(x+tx,y+dy,z+tz+dz) << t(x-dx,y+ty,z+tz) << getTexture((face & FACE_UP ? texture: tdef)) << 
		endl; // iso-z
	ret << t(x+tx-dx,y+ty+dy,z+tz) << t(x-dx,y+ty,z+tz) << t(x+tx-dx,y+ty+dy,z) << getTexture((face & FACE_REAR ? texture: tdef)) << endl; // iso-y
	ret << t(x+tx-dx,y+ty+dy,z+tz) << t(x+tx-dx,y+ty+dy,z) << t(x+tx,y+dy,z+tz) << getTexture((face & FACE_RIGHT ? texture: tdef)) << endl; // iso-x

	ret << t(x,y,z) << t(x+tx,y+dy,z+dz) << t(x-dx,y+ty,z) << getTexture((face & FACE_BOTTOM ? texture: tdef)) << endl; // iso-z
	ret << t(x,y,z) << t(x,y,z+tz) << t(x+tx,y+dy,z) << getTexture((face & FACE_FRONT ? texture: tdef)) << endl; // iso-y
	ret << t(x,y,z) << t(x-dx,y+ty,z) << t(x,y,z+tz) << getTexture((face & FACE_LEFT ? texture: tdef)) << endl; // iso-x
	ret << "}" << endl;
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

			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(hmap->gettex(xx,yy)) << endl; // iso-z
			ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(TEXTURE_CAULK) << endl; // iso-y
			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(TEXTURE_CAULK) << endl; // iso-x

			ret << t(x+tx,y+ty,z+tz+dc-10) << t(x,y+ty,z+tz+db-10) << t(x+tx,y,z+tz+da-10) << getTexture(TEXTURE_CAULK) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da) << t(x+tx,y,z+tz+da-10) << getTexture(TEXTURE_CAULK) << endl; 
			ret << "}\n";

			ret << "{\n";
			ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(hmap->gettex(xx,yy)) << endl; // iso-z
			ret << t(x,y+ty,z+da) << t(x+tx,y,z+tz+da-10) << t(x+tx,y,z+tz+da) << getTexture(TEXTURE_CAULK) << endl; 

			ret << t(x,y,z+tz-10) << t(x+tx,y,z+tz+da-10) << t(x,y+ty,z+tz+db-10) << getTexture(TEXTURE_CAULK) << endl; // iso-z
			ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+da+tz-10) << getTexture(TEXTURE_CAULK) << endl; // iso-y
			ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(TEXTURE_CAULK) << endl; // iso-x
			ret << "}\n";

		}else{ if(dc - da !=db ){


			ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y,z+tz+da) << t(x,y+ty,z+tz+db) << getTexture(hmap->gettex(xx,yy)) << endl; // iso-z
		}
		else{

			ret << "//pave" << endl;
		}
		ret << t(x,y,z+tz) << t(x,y+ty,z+tz+db) << t(x+tx,y,z+tz+da) << getTexture(hmap->gettex(xx,yy)) << endl; // iso-z
		ret << t(x+tx,y+ty,z+tz+dc) << t(x,y+ty,z+tz+db) << t(x+tx,y+ty,z+tz+dc-10) << getTexture(TEXTURE_CAULK) << endl; // iso-y
		ret << t(x+tx,y+ty,z+tz+dc) << t(x+tx,y+ty,z+tz+dc-10) << t(x+tx,y,z+tz+da) << getTexture(TEXTURE_CAULK) << endl; // iso-x

		//carre 
		ret << t(x,y,z+tz+ds-10) << t(x+tx,y,z+tz+ds-10) << t(x,y+ty,z+tz+ds-10) << getTexture(TEXTURE_CAULK) << endl; // iso-z

		ret << t(x,y,z+tz-10) << t(x,y,z+tz) << t(x+tx,y,z+tz+da-10) << getTexture(TEXTURE_CAULK) << endl; // iso-y
		ret << t(x,y,z+tz-10) << t(x,y+ty,z+tz+db-10) << t(x,y,z+tz) << getTexture(TEXTURE_CAULK) << endl; // iso-x
		ret  <<  "}\n";

		}
	}
	/*
	   if(hmap->gettex(xx,yy)>TEXTURE_TER5 && hmap->gettex(xx,yy)<=TEXTURE_TER4_5){
	   ret << endl << makeFace(x+tx/2,y+ty/2,z+tz+20,10,10,10,0,0,0,TEXTURE_ALPHA_50,FACE_ALL) << endl ;
	   }
	   */
	return ret.str();
}

