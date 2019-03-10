#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"
#include "gold.hpp"
using namespace std;

// note: no need to recreate methods that are inherited from materials (Andrew)

Gold::Gold(){
	color = "Golden-Yellow";
	uses = "Currency, jewelry, electronics, medicine, food coloring(pure gold is not poisonous, but impure gold is), and vehicle parts.";
	state = "Solid";
	form = "Au";
	price = 42.37;//dollars per grams (as of 2018)
	mass = 197;//In grams
	volume = 0.052;//In cubic centimeters for a gram of gold
}
