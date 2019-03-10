#include <iostream>
#include <string>
#include "allMaterials.hpp"
using namespace std;

int main(){
	Material m;
	Gold g;
	Silver s;
	Titanium t;

	cout << "Mass of material: " << m.getMass() << endl;
	cout << "Mass of gold: " << g.getMass() << endl;
	cout << "Mass of silver: " << s.getMass() << endl;
	cout << "Mass of titanium: " << t.getMass() << endl;

	return 0;
}
