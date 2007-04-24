#ifndef _HAVE_ENTITY_H
#define _HAVE_ENTITY_H

#include <list>
#include <iterator>

using namespace std;

typedef struct{
	string name;
	string value;
}args;


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
		string attrList(void);
		
		string toStr(void);
};

class Entities{
	private:
		list <Entity> entities;
	public:
		void entityAdd(Entity ent);
		void entityDelAll(void);
		int entityNbr(void);

		Entity * entityAt(int pos); // Pos = -1 : Last entity, -2, etc..
		Entity * entityFind(string name);
		list <Entity*> entitiesFilter(string name);
		list <Entity*> entitiesFilter(string name, string value);
		list <Entity*> entitiesFilter(string name, double value);
		
		void entitiesAttrAdd(string name, string value);
		void entitiesAttrAdd(string name, double value);
		void entitiesAttrMod(string name, string value);
		void entitiesAttrMod(string name, double value);
		
		void entitiesAttrDel(string name);
		
		string entitiesDump(void);
};


#endif // ENTITY_H
