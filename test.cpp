#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>

#include "entity.hpp"

int main(){
	
	Entities objs;

	//Entity toto("toto");
	//Entity tata("tata",20,30,42.5);
	Entity titi("titi",20,30,42.5,1.0);
	
	titi.attrAdd("model","c:\\");	
	titi.attrAdd("vue","face");	
	titi.attrAdd("scale","0.3");

	objs.entityAdd(titi);
	titi.attrAdd("scale","0.5");
	objs.entityAdd(titi);
	cout << objs.entityNbr() << endl;
	
	cout << titi.attrNbr() << endl;
	titi.attrList();	

	titi.attrDel("vue");
	cout << titi.attrNbr() << endl;
	titi.attrList();

	titi.attrMod("scale","0.7");
	titi.attrAdd("model","d:\\");	
	titi.attrAdd("z",40);	
	titi.attrAdd("angle",10);	
	cout << titi.z << endl;
	cout << titi.attrNbr() << endl;
	titi.attrList();

	Entity * test;
	if((test = objs.entityAt(0)) != NULL){
		cout << endl;
		test->attrMod("model","a:\\");	
	}
	if((test = objs.entityFind("titi")) != NULL){
		cout << endl;
		test->attrList();
	}
}
