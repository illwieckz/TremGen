#include <cstdlib>
#include <cstring>
#include <list>

using namespace std;

typedef struct{
	string nom;
	string val;
}args;

std::ostream& operator<< (std::ostream& out, args c)
{
  out << c.nom << " = " << c.val;
  return out ;
}

//La classe qui gere les entites
class Entity{
	private:

		
	public:
		string name;
		double x,y,z,angle;
		
		list <args> attr;
		
		Entity(string _name);
		Entity(string _name, double _x, double _y, double _z);
		Entity(string _name, double _x, double _y, double _z, double _angle);
		~Entity(void);
		
		void addAttr(void);
};

Entity::Entity(string _name):name(_name){
	x=y=z=angle=0.0;
}

Entity::Entity(string _name, double _x, double _y, double _z):name(_name), x(_x), y(_y), z(_z){
	angle=0.0;
}

Entity::Entity(string _name, double _x, double _y, double _z, double _angle):name(_name), x(_x), y(_y), z(_z), angle(_angle){
}

Entity::~Entity(void){
}

