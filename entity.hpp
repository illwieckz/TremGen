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
		double x,y,z;

		Entity(string _name);
		Entity(string _name, double _x, double _y, double _z);
		Entity(string _name, double _x, double _y, double _z, double _angle);

		void attrAdd(string name, string value);
		void attrAdd(string name, double value);
		void attrMod(string name, string value);
		void attrMod(string name, double value);
		args * attrFind(string name, string value);
		args * attrFind(string name, double value);
		void attrDel(string name);
		void attrDelAll(void);
		int attrNbr(void);
		void attrList(void);
};

Entity::Entity(string _name):name(_name){
	x=y=z=0.0;
}

Entity::Entity(string _name, double _x, double _y, double _z):name(_name), x(_x), y(_y), z(_z){
}

Entity::Entity(string _name, double _x, double _y, double _z, double _angle):name(_name), x(_x), y(_y), z(_z){
	attrMod("angle",_angle);
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

void Entity::attrAdd(string name, double value){

	if(name.size() == 1){
		switch(name[0]){
			case 'x':
				x = value;
				return;
			case 'y':
				y = value;
				return;
			case 'z':
				z = value;
				return;
		}
	}

	stringstream _value;
	_value << value;

	attrAdd(name, _value.str());
}

void Entity::attrList(void){
	copy(attr.begin(), attr.end(), ostream_iterator<args>(cout, "\n"));
}

void Entity::attrMod(string name, string value){
	attrAdd(name,value);
}

void Entity::attrMod(string name, double value){
	attrAdd(name,value);
}

args * Entity::attrFind(string name, string value){
	list<args>::iterator iter;


	for(iter = attr.begin(); iter != attr.end(); iter++){
		if(name.compare((*iter).name) == 0 && value.compare((*iter).value) == 0)
			return &(*iter); 
	}
	return NULL;
}

args * Entity::attrFind(string name, double value){

	stringstream _value;
	_value << value;

	return attrFind(name, _value.str());
}

void Entity::attrDel(string name){
	list<args>::iterator iter;

	iter = remove_if(attr.begin(),attr.end(),findAttrName(name));
	if(iter != attr.end()){
		attr.erase(iter);
	}
}

void Entity::attrDelAll(void){
	attr.clear();
}

int Entity::attrNbr(void){
	return attr.size();
}

/* TODO 
OK: entityAt() -> Entity;
OK: entityFind(name) -> Entity;
OK: entitiesFilter(name) -> Entities;
entitiesAddAttr() -> void (rajoute ou modifie un attribut tous les éléments) ;
entitiesDelAttr() -> void (delete un attribut tous les éléments);
entitiesTranslate(x,y,z);
*/

struct findEntityName
{
	findEntityName(const string& n) : name(n) {}

	bool operator()(const Entity& c) const{
		return c.name == name;
	}       

	private :
	string name;
};

class Entities{
	private:
		list <Entity> entities;
	public:
		void entityAdd(Entity ent);
		void entityDelAll(void);
		int entityNbr(void);

		Entity * entityAt(int pos);
		Entity * entityFind(string name);
		list <Entity*> entityFilter(string name);
		list <Entity*> entityFilter(string name, string value);
		list <Entity*> entityFilter(string name, double value);
};

void Entities::entityAdd(Entity ent){
	entities.push_back(ent);
}

	Entity * Entities::entityAt(int pos){
		if(entities.empty())
			return NULL;

		if(pos >= (int)entities.size())
			return NULL;

		list<Entity>::iterator iter;

		iter = entities.begin();
		for(int i=0; i < pos; i++, iter++);

		return &(*iter);
	}

Entity * Entities::entityFind(string name){
	list<Entity>::iterator iter;

	iter = find_if(entities.begin(),entities.end(),findEntityName(name));
	if(iter != entities.end()){
		return &(*iter);
	}
	return NULL;
}

list <Entity*> Entities::entityFilter(string name, string value){
	list<Entity>::iterator iter;
	list<Entity*> elist;

	for(iter = entities.begin(); iter != entities.end(); iter++){
		if((*iter).attrFind(name,value) != NULL)
			elist.push_back(&(*iter));
	}
	return elist;

}

list <Entity*> Entities::entityFilter(string name, double value){
	list<Entity>::iterator iter;
	list<Entity*> elist;

	if(name.size() == 1){
		switch(name[0]){
			case 'x':
			for(iter = entities.begin(); iter != entities.end(); iter++){
				if((*iter).x == value)
					elist.push_back(&(*iter));
			}
			return elist;
			case 'y':
			for(iter = entities.begin(); iter != entities.end(); iter++){
				if((*iter).y == value)
					elist.push_back(&(*iter));
			}
			return elist;
			case 'z':
			for(iter = entities.begin(); iter != entities.end(); iter++){
				if((*iter).z == value)
					elist.push_back(&(*iter));
			}
			return elist;
		}
	}

	stringstream _value;
	_value << value;
	return entityFilter(name,_value.str());
}

list <Entity*> Entities::entityFilter(string name){
	list<Entity>::iterator iter;
	list<Entity*> elist;

	for(iter = entities.begin(); iter != entities.end(); iter++){
		if(name.compare((*iter).name) == 0)
			elist.push_back(&(*iter));
	}
	return elist;
}

void Entities::entityDelAll(void){
	entities.clear();
}

int Entities::entityNbr(void){
	return entities.size();
}

