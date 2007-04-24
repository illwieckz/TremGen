#ifndef _HAVE_MAP_H
#define _HAVE_MAP_H

#define AT(wh,x,y) (wh[(x)*ysize+(y)])
#define ALT(x,y) (map[(x)*ysize+(y)])
#define ALTD(x,y) (dmap[(x)*ysize+(y)])
#define TEXM(x,y) (AT(tmap,x,y))
#define IWATER(x,y) (wmap[(x)*ysize+(y)])
#define getRnd(X) (double)(X*2 * ((random()+0.0) / (RAND_MAX ) - 0.5))
#define maxabs(x,y,z) ((abs(x)>abs(y)?(abs(x)>abs(z)?x:z):(abs(y)>abs(z)?y:z)))
//pas besion de tester avec 0 c'est le min de ce que renvoi abs 

#define BORDERFACT (1.4)

using namespace std;

class AltitudeMap{
	private:
		double * map;
		double * dmap; /*diff map*/
		int * tmap; /*textures map*/
		char * wmap; /* water map */

		double alien_pos_x;
		double alien_pos_y;
		double human_pos_x;
		double human_pos_y;

		void subdiv_private(double coeff, int x1, int y1, int x2, int y2);
		void maketextures(void);	

	public:
		int xsize,ysize;
		double sealevel;

		AltitudeMap(int _xsize, int _ysize);
		~AltitudeMap(void);

		double getaltitude(int x, int y);

		void setHumanPos(double x, double y);
		void setAlienPos(double x, double y);

		double getHumanPosX(void);
		double getAlienPosX(void);
		double getHumanPosY(void);
		double getAlienPosY(void);


		/*diff fct*/
		double getdiff(int x, int y);
		void makediff(void);
		/*end diff fct*/

		int  texchooser(double criteria);	
		int gettex(int x, int y);

		void setwater(int x, int y, char level);
		char getwater(int x, int y);

		double getmaxalt(void);
		double getminalt(void);

		void randomize(double r);
		void subdivision(double coeff, double lt, double rt, double lb, double rb);
		void erosion(int r, int iter);
		void normalize(void);
};


#endif // MAP_H
