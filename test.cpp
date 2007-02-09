#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>

#include "entity.hpp"

int main(){
	Entity toto("toto");
	Entity tata("tata",20,30,42.5);
	Entity titi("titi",20,30,42.5,1.0);
	
	titi.attrAdd("model","c:\\");	
	titi.attrAdd("vue","face");	
	titi.attrAdd("scale","0.5");	
	
	cout << titi.attrNbr() << endl;
	titi.attrList();	

	titi.attrDel("vue");
	cout << titi.attrNbr() << endl;
	titi.attrList();

	titi.attrMod("scale","0.7");
	titi.attrAdd("model","d:\\");	
	cout << titi.attrNbr() << endl;
	titi.attrList();
	
}
