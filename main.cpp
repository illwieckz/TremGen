#include "main.h"
#include "math.h"

#include "entity.h"
#include "meshes.h"
#include "envgen.h"
#ifndef MESSAGE
#define MESSAGE "http://labs.esiea.fr"
#endif

#define real(x,y) (getRealAlt(hmap,x,y,TSIZE,TSIZE,HINC)+30)
#define normal(x,y) (getNormalDiff(hmap,x,y,TSIZE,TSIZE,HINC))

typedef struct tagEntities_group{
	Entities aliens;
	Entities humans;
	Entities infos;

	Entities misc;
}Entities_group;

string getHeader(int xsize, int ysize){
	stringstream ret;
	ret << "//entity 0\n";
	ret << "{\n\"classname\" \"worldspawn\"\n";
	ret << "\"_blocksize\" \"16384 16384 16384\"\n"; //seemingly useless
	ret << "\"message\" \"map from heightmap " << xsize << "x" << ysize << " "<< MESSAGE<<"\"\n";

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
float getNormalDiff(AltitudeMap * hmap ,double x, double y,double tx,double ty, double itz)
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
	//cf schema en dessous
	//(tx,0,db)
	//(0,ty,da)
	//Vect=(-ty*db,-tx*da,tx*ty)
	//N0=(0,0,tx*ty)
	//cos=adj/hy
	
//        fprintf(stderr,"t:%f %f %f %f %f\n",(float)sqrt((ty*db*db*ty+tx*da*tx*da+tx*ty*ty*tx)),db,da*tx,tx*tx*ty*ty,ty*db*db*ty);
	return (float)sqrt((tx*ty*tx*ty)/(float)(ty*db*db*ty+tx*da*tx*da+tx*ty*ty*tx));
	
	}else{
	//(-tx,0,db-dc)
	//(0,-ty,da-dc)
	//Vect=((db-dc) *ty ,(da-dc)*tx,tx*ty)
	//N0=(0,0,tx*ty)
	
	return (float)sqrt((tx*ty*ty*tx)/(float)(ty*(db-dc)*(db-dc)*ty+tx*(da-dc)*tx*(da-dc)+tx*ty*ty*tx));

	}

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
#ifdef DEBUG				
					fprintf(stderr,"Bye Bye Forest!\n");
#endif					
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

	double al=real(x*TSIZE,y*TSIZE);

	int lx=(int)floor(x);
	int ly=(int)floor(y);
	al+=hmap->getaltitude(lx-1,ly);
	al+=hmap->getaltitude(lx,ly-1);
	al+=hmap->getaltitude(lx+1,ly);
	al+=hmap->getaltitude(lx,ly+1);

	if(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || notinarena(lx,ly,x,y) || normal(x*TSIZE,y*TSIZE)<0.95f ) //dans l'eau ou hors map
		return 0;
	//fprintf(stderr,"--%f\n",al/(max*HINC));
	return 1-((al/5.0)/(max*HINC));
}


double mesureHuman(double x, double y,double dist,double max,AltitudeMap * hmap)
{

	double al=real(x*TSIZE,y*TSIZE);
//fprintf(stderr,"xy %f %f\n",x,y);
	int lx=(int)floor(x);
	int ly=(int)floor(y);
	al+=hmap->getaltitude(lx-1,ly);
	al+=hmap->getaltitude(lx,ly-1);
	al+=hmap->getaltitude(lx+1,ly);
	al+=hmap->getaltitude(lx,ly+1);
//fprintf(stderr,"dist:%f\n",dist);
//fprintf(stderr,"p:%f %f\n",dist*TSIZE,(MAPSIZE/4.0)*TSIZE);
	if(hmap->getwater(lx,ly) == TWATER || hmap->getwater(lx,ly) == CENTER || notinarena(lx,ly,x,y) || normal(x*TSIZE,y*TSIZE)<0.95f || dist<(MAPSIZE/3.0)*TSIZE){ //dans l'eau ou hors map
//fprintf(stderr,"norm :%f\n",normal(x*TSIZE,y*TSIZE));

		return 0;

}
//fprintf(stderr,"p:%f %f\n",dist,(MAPSIZE/4.0)*TSIZE);
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
#ifdef DEBUG
		fprintf(stderr,"%f %f %f\n",px,py,mesureAlien(px,py,max,hmap));
#endif		
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




		tmp=hmap->getAlienPosX()-px*TSIZE;
		tmp*=tmp;

		double tmp2=hmap->getAlienPosY()-py*TSIZE;
		tmp2*=tmp2;

		tmp+=tmp2;
		tmp=sqrt(tmp);
#ifdef DEBUG
		fprintf(stderr,"%f %f %f\n",px,py,mesureHuman(px,py,tmp,max,hmap));
#endif		
		stop--;
		if(stop==0)
		{
			stop=50;
			seuil-=seuil/10;
			fprintf(stderr,"Descente seuil Human : %f \n",seuil);
		}

	}while(mesureHuman(px,py,tmp,max,hmap)<seuil);

//		fprintf(stderr,"final %f %f\n",normal(px*TSIZE,py*TSIZE),mesureHuman(px,py,tmp,max,hmap));
	px*=TSIZE;
	py*=TSIZE;
 //fprintf(stderr,"final dist %f %f %f %f %f \n",tmp,px,py,hmap->getAlienPosX(),hmap->getAlienPosY());

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

	if(argc>1)
	{
	
	srand(atoi(argv[1]));
	}else{
	srand(time(NULL));
	}

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

