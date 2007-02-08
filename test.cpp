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
	
	cout << toto.name << endl;
	cout << tata.name << endl;
	cout << tata.x << endl;
	cout << toto.x << endl;
	cout << titi.angle << endl;
	
	args tutu;
	tutu.name = "model";
	tutu.value = "c:";
	titi.attr.push_back(tutu);
	tutu.name = "scale";
	tutu.value = "7.0";
	titi.attr.push_back(tutu);
	//titi.li.insert(++titi.li.begin(),1);
	copy(titi.attr.begin(), titi.attr.end(), ostream_iterator<args>(cout, " "));
}
