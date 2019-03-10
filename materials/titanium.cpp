#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"
#include "titanium.hpp"
using namespace std;

// note: no need to recreate methods that are inherited from materials (Andrew)

Titanium::Titanium(){
	color = "Purple";
	uses = "Coloring, coating, building ships(space, air and marine ships), industry, architecture, cars and motorcycles, jewelry, medial equipment, and nuclear waste storage.";
	state = "Solid";
	form = "Ti";
	price = 6.61;//dollars per grams (as of 2018)
	mass = 48;//In grams
	volume = 0.22;//In cubic centimeters for a gram of titanium
}
