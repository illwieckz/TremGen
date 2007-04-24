#include "main.h" 
#include "entity.h"

std::ostream& operator<< (std::ostream& out, args c)
{
        out << "\"" << c.name << "\" \"" << c.value << "\"";
        return out ;
}

/***/

Entity::Entity(string _name):name(_name){
	x=y=z=0.0;
}

Entity::Entity(string _name, double _x, double _y, double _z):name(_name), x(_x), y(_y), z(_z){
}

Entity::Entity(string _name, double _x, double _y, double _z, double _angle):name(_name), x(_x), y(_y), z(_z){
	attrMod("angle",_angle);
}

string Entity::toStr(void){
        stringstream ret;

        ret << "{" << endl;
        ret << "\"classname\" \"" << name << "\"" << endl;
        ret << "\"origin\" \"" << x << " " << y << " " << z << "\"" << endl;
       	ret << this->attrList(); 
	ret << "}" << endl;

        return ret.str();
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

string Entity::attrList(void){
	stringstream ret;
	copy(attr.begin(), attr.end(), ostream_iterator<args>(ret, "\n"));
	return ret.str();
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


/* Entities Class Methods */

void Entities::entityAdd(Entity ent){
	entities.push_back(ent);
}

	Entity * Entities::entityAt(int pos){
		if(entities.empty())
			return NULL;

		if(abs(pos) >= (int) (entities.size() + (pos < 0 ? 1:0)))
			return NULL;

		list<Entity>::iterator iter;

		if(pos >= 0){
			iter = entities.begin();
			for(int i=0; i < pos; i++, iter++);
		}else{
			iter = entities.end();
			for(int i=0; i > pos; i--, iter--);
		}

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

list <Entity*> Entities::entitiesFilter(string name, string value){
	list<Entity>::iterator iter;
	list<Entity*> elist;

	for(iter = entities.begin(); iter != entities.end(); iter++){
		if((*iter).attrFind(name,value) != NULL)
			elist.push_back(&(*iter));
	}
	return elist;

}

list <Entity*> Entities::entitiesFilter(string name, double value){
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
	return entitiesFilter(name,_value.str());
}

list <Entity*> Entities::entitiesFilter(string name){
	list<Entity>::iterator iter;
	list<Entity*> elist;

	for(iter = entities.begin(); iter != entities.end(); iter++){
		if(name.compare((*iter).name) == 0)
			elist.push_back(&(*iter));
	}
	return elist;
}

void Entities::entitiesAttrAdd(string name, string value){
        list<Entity>::iterator iter;
        
        for(iter = entities.begin(); iter != entities.end(); iter++){
                (*iter).attrAdd(name, value);
        }               
        return ;
}

void Entities::entitiesAttrAdd(string name, double value){
        list<Entity>::iterator iter;

        for(iter = entities.begin(); iter != entities.end(); iter++){
                (*iter).attrAdd(name, value);
        }
}

void Entities::entitiesAttrMod(string name, string value){
	entitiesAttrAdd(name,value);
}

void Entities::entitiesAttrMod(string name, double value){
        entitiesAttrAdd(name,value);
}

void Entities::entitiesAttrDel(string name){
        list<Entity>::iterator iter;
        
        for(iter = entities.begin(); iter != entities.end(); iter++){
                (*iter).attrDel(name);
        }               
        return ;
}

void Entities::entityDelAll(void){
	entities.clear();
}

int Entities::entityNbr(void){
	return entities.size();
}

string Entities::entitiesDump(void){
	static int e_id=1;
	stringstream ret;
	list<Entity>::iterator iter;

        for(iter = entities.begin(); iter != entities.end(); iter++, e_id++){
		ret << "// entity " << e_id << endl ;
                ret << (*iter).toStr();
        }

	return ret.str();
}

