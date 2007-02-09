#include <cstdlib>
#include <cstring>
#include <list>

using namespace std;

typedef struct{
	string name;
	string value;
}args;

std::ostream& operator<< (std::ostream& out, args c)
{
	out << "(" << c.name << " = \"" << c.value << "\")";
	return out ;
}

class Entity{
	private:
		list <args> attr;
	public:
		string name;
		double x,y,z,angle;

		Entity(string _name);
		Entity(string _name, double _x, double _y, double _z);
		Entity(string _name, double _x, double _y, double _z, double _angle);
		~Entity(void);

		void attrAdd(string name, string value);
		void attrMod(string name, string value);
		void attrDel(string name);
		int attrNbr(void);
		void attrList(void);
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

struct findAttrName
{
	findAttrName(const string& n) : name(n) {}

	bool operator()(const args& c) const{
		return c.name == name;
	}

	private :
	string name;
};

void Entity::attrAdd(string name, string value){
	list<args>::iterator iter;
	
	iter = find_if(attr.begin(),attr.end(), findAttrName(name));

	if(iter == attr.end()){
		args elt;

		elt.name = name;
		elt.value = value;
		attr.push_back(elt);
	}else
		(*iter).value = value;
}

void Entity::attrList(void){
	copy(attr.begin(), attr.end(), ostream_iterator<args>(cout, "\n"));
}

void Entity::attrMod(string name, string value){
	attrAdd(name,value);
}

void Entity::attrDel(string name){
	list<args>::iterator iter;

	iter = remove_if(attr.begin(),attr.end(),findAttrName(name));
	if(iter != attr.end()){
		attr.erase(iter);
	}
}

int Entity::attrNbr(void){
	return attr.size();
}

