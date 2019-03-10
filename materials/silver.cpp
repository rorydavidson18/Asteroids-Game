#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"
#include "silver.hpp"
using namespace std;

// note: no need to recreate methods that are inherited from materials (Andrew)

Silver::Silver(){
	color = "Gray";
	uses = "Currency, jewelry, silverware, medicine, electronics, alloys, chemical equipment, photography, and food coloring (pure silver isn't poisonous, but impure silver is).";
	state = "Solid";
	form = "Ag";
	price = 0.53;//dollars per grams (as of 2018)
	mass = 108;//In grams
	volume = 0.095;//In cubic centimeters for a gram of silver
}
