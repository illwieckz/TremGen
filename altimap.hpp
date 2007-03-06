#include <cmath>
#include <cstdlib>
#include <ctime>

#define ALT(x,y) (map[(x)*ysize+(y)])
#define ALTD(x,y) (dmap[(x)*ysize+(y)])
#define getRnd(X) (double)(X*2 * ((random()+0.0) / (RAND_MAX ) - 0.5))
#define maxabs(x,y,z) ((abs(x)>abs(y)?(abs(x)>abs(z)?x:z):(abs(y)>abs(z)?y:z)))
//pas besion de tester avec 0 c'est le min de ce que renvoi abs 

using namespace std;

class AltitudeMap{
	private:
		double * map;
		double * dmap; /*diff map*/

		void subdiv_private(double coeff, int x1, int y1, int x2, int y2);
		

	public:
		int xsize,ysize;
		double sealevel;

		AltitudeMap(int _xsize, int _ysize);
		~AltitudeMap(void);

		double getaltitude(int x, int y);

		/*diff fct*/
		double getdiff(int x, int y);
		void makediff(void);
		/*end diff fct*/
		double getmaxalt(void);
		double getminalt(void);

		void randomize(double r);
		void subdivision(double coeff, double lt, double rt, double lb, double rb);
		void erosion(int r, int iter);
		void normalize(void);
};


AltitudeMap::AltitudeMap(int _xsize, int _ysize):xsize(_xsize),ysize(_ysize),sealevel(0.0){
	srandom(time(NULL));

	map = new double[xsize*ysize];

	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y)
			ALT(x,y) = 0.0;
	dmap=NULL;
}

AltitudeMap::~AltitudeMap(void){
	delete [] map;
	if(dmap!=NULL)
	{
	
	delete [] dmap;
	}
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

	srand(time(NULL));

	subdiv_private(coeff,0,0,xsize-1,ysize-1);
	for(int x=0; x < xsize; ++x)
		for(int y=0; y < ysize; ++y){
			ALT(x,y) += 0.5;
			if(ALT(x,y) > 1.0) ALT(x,y) = 1.0;
			if(ALT(x,y) < 0.0) ALT(x,y) = 0.0;
		}
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
