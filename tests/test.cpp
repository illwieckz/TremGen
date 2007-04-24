#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>

#include "entity.hpp"

int main(){
	
	Entities objs;

	//Entity toto("toto");
	Entity tata("tata",20,30,42.5);

	objs.entityAdd(tata);

	Entity titi("titi",40,30,42.5,1.0);
	
	titi.attrAdd("model","c:\\");	
	titi.attrAdd("vue","face");	
	titi.attrAdd("scale","0.3");

	objs.entityAdd(titi);
	titi.attrAdd("scale","0.5");
	objs.entityAdd(titi);
	//cout << objs.entityNbr() << endl;
	
	objs.entitiesAttrAdd("tada",1.2);
	objs.entitiesAttrAdd("tapouet",4);
	objs.entitiesAttrMod("x",1);
	objs.entitiesAttrDel("tapouet");
	
	//cout << titi.attrNbr() << endl;
	//cout << titi.attrList();	

	titi.attrDel("vue");
	//cout << titi.attrNbr() << endl;
	//cout << titi.attrList();

	titi.attrMod("scale","0.7");
	titi.attrAdd("model","d:\\");	
	titi.attrAdd("z",40);	
	titi.attrAdd("angle",10);
		
	//cout << titi.z << endl;
	//cout << titi.attrNbr() << endl;
	//cout << titi.attrList();

	Entity * test;
	if((test = objs.entityAt(1)) != NULL){
		//cout << endl;
		test->attrMod("model","a:\\");	
	}
	if((test = objs.entityAt(0)) != NULL){
		//cout << endl;
		//cout << test->toStr();	
	}
	if((test = objs.entityFind("titi")) != NULL){
                //cout << (*test).attrList();
		//cout << endl;
	}

	list<Entity*> elist;
	elist = objs.entitiesFilter("tata");

        list<Entity*>::iterator itest;
        for(itest = elist.begin(); itest != elist.end(); itest++){
                //cout << (*itest)->name << endl;
		(*itest)->attrAdd("pouet",1);
	}

	elist = objs.entitiesFilter("z",42.5);

        for(itest = elist.begin(); itest != elist.end(); itest++){
                //cout << (*itest)->name << endl;
		//cout << "x: " << (*itest)->x << endl;
	}

	cout << objs.entitiesDump();

}
