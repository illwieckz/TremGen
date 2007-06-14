#include "main.h"

#include "altimap.h"

AltitudeMap::AltitudeMap(int _xsize, int _ysize):xsize(_xsize),ysize(_ysize),sealevel(0.0){
//	srandom(time(NULL));
	xsize+=3;
	ysize+=3;
	map = new double[xsize*ysize];

	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y)
			ALT(x,y) = 0.0;
	dmap=NULL;
	tmap=NULL;

	wmap = new char[xsize*ysize];
	for(int x=0;x<xsize;++x)
		for(int y=0;y<ysize;++y)
			IWATER(x,y) = 0;
}

AltitudeMap::~AltitudeMap(void){
	delete [] map;
	if(dmap!=NULL)
		delete [] dmap;
	if(tmap!=NULL)
		delete [] tmap;
	delete [] wmap;
}

	double AltitudeMap::getaltitude(int x, int y){
		if(x < xsize && y < ysize)
			return ALT(x,y);
		return 0;
	}

	double AltitudeMap::getdiff(int x, int y){
		if(dmap==NULL)
		{
			makediff();
		}
		if(x < xsize && y < ysize)
			return ALTD(x,y);
		return 0;
	}


void AltitudeMap::setHumanPos(double x, double y)
{
	human_pos_x=x;
	human_pos_y=y;
}


void AltitudeMap::setAlienPos(double x, double y)
{
	alien_pos_x=x;
	alien_pos_y=y;
}

double AltitudeMap::getHumanPosX (void)
{
	return human_pos_x;
}

double AltitudeMap::getHumanPosY (void)
{
	return human_pos_y;
}


double AltitudeMap::getAlienPosX (void)
{
	return alien_pos_x;
}


double AltitudeMap::getAlienPosY (void)
{
	return alien_pos_y;
}

void AltitudeMap::makediff(void)
{
	double itz=10;
	dmap = new double[xsize*ysize];
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			double tz=itz*getaltitude(x,y)*255+20;
			double da=(itz*getaltitude(x+1,y)*255+20)-tz;
			double db=(itz*getaltitude(x,y+1)*255+20)-tz;
			double dc=(itz*getaltitude(x+1,y+1)*255+20)-tz;	

			ALTD(x,y) = maxabs(da,db,dc);
		}

}

	void AltitudeMap::setwater(int x, int y, char level){
		if(x < xsize && y < ysize)
			IWATER(x,y) = level;
	}

	char AltitudeMap::getwater(int x, int y){
		if(x < xsize && y < ysize)
			return IWATER(x,y);
		return 0;
	}

int textchooser(double criteria)
{

	/** Pour l'instant critere sur la diff */
	if(abs(criteria)<50){
		return TEXTURE_TER1;
	}

	if(abs(criteria)<105){
		return TEXTURE_TER2;
	}

	if(abs(criteria)<160){
		return TEXTURE_TER3;
	}

	return TEXTURE_TER4;

	/*if(abs(z)< 80) //(255*HINC*0.2))
	  {

	  }*/




}


	int AltitudeMap::gettex(int x, int y){
		if(tmap==NULL)
		{
			maketextures();
		}
		if(x < xsize && y < ysize)
			return TEXM(x,y);
		return 1000; //defval
	}

void AltitudeMap::maketextures(void)
{
	tmap = new int[xsize*ysize];
	//int *	tmap2 = new int[xsize*ysize];
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){


			TEXM(x,y) =textchooser( getdiff(x,y));
			//AT(tmap2,x,y)=TEXM(x,y);
		}

	//supression des textures encercles
	//test non-optimal mais plus simple
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			int tcomp=gettex(x-1,y-1);
			if(	   tcomp==gettex(x-1,y)
					&& tcomp==gettex(x-1,y+1)
					&& tcomp==gettex(x,y-1)
					&& tcomp==gettex(x,y+1)
					&& tcomp==gettex(x+1,y-1)
					&& tcomp==gettex(x+1,y)
					&& tcomp==gettex(x+1,y+1)
					&& tcomp!=gettex(x,y)
			  )
			{
				TEXM(x,y)=tcomp;			
			}
		}
	/*
	//Gestion des interfaces

	for(int x=1; x < xsize-1; ++x)
	for(int y=0; y < ysize; ++y){
	if(gettex(x-1,y)!=gettex(x+1,y))
	AT(tmap2,x,y)=gettex(x-1,y)+gettex(x+1,y);
	}




	//copie des res on doit pouvoir faire mieux mais la c'est sûr

	for(int x=0; x < xsize; ++x)
	for(int y=0; y < ysize; ++y){
	TEXM(x,y)=AT(tmap2,x,y);
	}
	delete [] tmap2;
	*/

}

double AltitudeMap::getmaxalt(void){
	double max=ALT(0,0);
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			if(ALT(x,y) > max) max = ALT(x,y);
		}
	return max;
}

double AltitudeMap::getminalt(void){
	double min=ALT(0,0);
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			if(ALT(x,y) < min) min = ALT(x,y);
		}
	return min;
}

void AltitudeMap::subdivision(double coeff, double lt, double rt, double lb, double rb){
	ALT(xsize-1,0) = rt;
	ALT(0,ysize-1) = lb;
	ALT(xsize-1,ysize-1) = rb;

//	srand(time(NULL));

	subdiv_private(coeff,3,3,xsize-4,ysize-4);
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			ALT(x,y) += 0.5;
			if(ALT(x,y) > 1.0) ALT(x,y) = 1.0;
			if(ALT(x,y) < 0.0) ALT(x,y) = 0.0;
		}
	//bord
	for(int x=0; x < xsize; ++x){
		for(int y=0; y < ysize; ++y){
			if(x>(xsize-4))
			{
				ALT(x,y)=BORDERFACT*ALT(x-1,y);
			}


			if(y>(ysize-4))
			{

				ALT(x,y)=BORDERFACT*ALT(x,y-1);
			}
		}
	}


	for(int x=xsize-1; x >= 0; --x){
		for(int y=ysize-1; y >=0 ; --y){
			if(x<3)
			{
				ALT(x,y)=BORDERFACT*ALT(x+1,y);
			}


			if(y<3)
			{

				ALT(x,y)=BORDERFACT*ALT(x,y+1);
			}
		}
	}

	//coins

	for(int x=0; x < xsize; ++x){
		for(int y=0; y < ysize; ++y){
			float X=x-xsize/2.0;
			float Y=y-ysize/2.0;
			if(X==Y || X==-Y )
			{
				if(x>(xsize-4))
				{
					ALT(x,y)=BORDERFACT*ALT(x-1,y-1);
				}

			}

		}
	}

	for(int x=xsize-1; x >= 0; --x){
		for(int y=ysize-1; y >=0 ; --y){
			float X=x-xsize/2.0;
			float Y=y-ysize/2.0;
			if(x==y || X==-Y )
			{
				if(x<3)
				{
					ALT(x,y)=BORDERFACT*ALT(x+1,y+1);
				}

			}
		}
	}


	for(int x=0; x < xsize; ++x){
		for(int y=0; y < ysize; ++y){

			float X=x-xsize/2.0;
			float Y=y-ysize/2.0;
			if((x<3 || x>(xsize-4)) && ( y<3 || y>(ysize-4)) && X!=Y && X!=-Y)
			{
				//			fprintf(stderr,"%d %d\n",x,y);
				if(X<Y && Y>-X)
				{//horiz
					int in=3-y+1;
					float c1=(3-x)/3.0;
					if(y>ysize/2.0)
					{
						in=-(3-(ysize-y));

					}

					if(x>xsize/2.0){
						c1=(x-(xsize-3))/3.0;
					}
					float c2=1.0-c1;

					//			fprintf(stderr,"%f %f %f %f\n",c1,ALT(y,y),c2,ALT((y+in),y));
					ALT(x,y)=c2*ALT(y,y)+c1*ALT((y+in),y);
				}else
				{//vert

					int in=3-x+1;
					float c1=(3-y)/3.0;
					if(x>xsize/2.0)
					{
						in=-(3-(xsize-x));

					}

					if(y>ysize/2.0){
						c1=(y-(ysize-3))/3.0;
					}
					float c2=1.0-c1;

					//			fprintf(stderr,"%f %f %f %f\n",c1,ALT(y,y),c2,ALT((y+in),y));
					ALT(x,y)=c2*ALT(x,x)+c1*ALT(x,(x+in));






				}
			}
		}
	}
	//renormalization	
	normalize();
}


void AltitudeMap::subdiv_private(double coeff, int x1, int y1, int x2, int y2){

	if(abs(double(x1-x2)) <= 1 || abs(double(y1-y2)) <= 1) return;

	int xmiddle = x1 + (int)floor(double(x2-x1)/2.0);
	int ymiddle = y1 + (int)floor(double(y2-y1)/2.0);

	ALT(xmiddle,y1) = (ALT(x1,y1) + ALT(x2,y1))/2.0 + getRnd(0.5) * coeff;
	ALT(x1,ymiddle) = (ALT(x1,y1) + ALT(x1,y2))/2.0 + getRnd(0.5) * coeff;
	ALT(xmiddle,ymiddle) = (ALT(x1,y1) + ALT(x2,y2))/2.0 + getRnd(0.5) * coeff;
	ALT(xmiddle,y2) = (ALT(x1,y2) + ALT(x2,y2))/2.0 + getRnd(0.5) * coeff;
	ALT(x2,ymiddle) = (ALT(x2,y1) + ALT(x2,y2))/2.0 + getRnd(0.5) * coeff;

	coeff *= coeff;
	subdiv_private(coeff,x1,y1,xmiddle,ymiddle);
	subdiv_private(coeff,xmiddle,y1,x2,ymiddle);
	subdiv_private(coeff,x1,ymiddle,xmiddle,y2);
	subdiv_private(coeff,xmiddle,ymiddle,x2,y2);
}

void AltitudeMap::randomize(double r){
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			ALT(x,y) = ALT(x,y) + getRnd(r);
			if(ALT(x,y) < 0.0) ALT(x,y) = 0.0;
			else if(ALT(x,y) > 1.0) ALT(x,y) = 1.0;
		}
}

void AltitudeMap::erosion(int r, int iter){
	double * copy;
	copy = new double[xsize*ysize];

	while(iter--){

		for(int x=0; x < xsize; x++)
			for(int y =0; y < ysize; y++){
				double sum=0.0;
				int offx,offy,p=0;

				for(offx=-r;offx<=r;offx++){
					for(offy=-r;offy<=r;offy++){
						int X=x+offx;
						int Y=y+offy;

						if(X<0 || Y <0 || X>=xsize|| Y>= ysize ) 
							continue;
						sum += ALT(X,Y);
						p++;
					}

				}
				if(p!=0)
					copy[x*ysize+y] = (sum+0.0)/(p);
				else

					copy[x*ysize+y] = 0.0;

			}
		for(int x=0; x < xsize; ++x)
			for(int y=0; y < ysize; ++y){
				ALT(x,y) = copy[x*ysize+y];
			}

	}
	delete [] copy;
}

void AltitudeMap::normalize(){
	double min = getminalt();

	for(int x=0; x < xsize; x++)
		for(int y =0; y < ysize; y++){
			ALT(x,y) = ALT(x,y) - min;
		}
}
