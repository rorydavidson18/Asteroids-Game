#include <iostream> //may need more includes, but this is the basics
#include <string>
#include "material.hpp"
using namespace std;

Material::Material(){//default constructor
	color = "None";
	uses = "None";
	state = "N/A";
	form = "None";
	price = 0.0;
	mass = 0;
	volume = 0.0;
}

std::string Material::getColor(){//returns color of material
	return color;
}

std::string Material::getUses(){//returns uses of material
	return uses;
}

std::string Material::getState(){//returns matter state of material
	return state;
}

std::string Material::getForm(){//returns chemical formula of material
	return form;
}

std::string Material::summary(){
	std::string str;
	str += "Color: " + color + "\n";
	str += "Uses: " + uses + "\n";
	str += "State of matter: " + state + "\n";
	str += "Chemical formula: " + form + "\n";
	std::string p = std::to_string(price);
	std::string m = std::to_string(mass);
	std::string v = std::to_string(volume);
	str += "Price: " + p + "\n";
	str += "Mass: " + m + "\n";
	str += "Volume: " + v + "\n";
	return str;
}

double Material::getPrice(){//returns price of material
	return price;
}

int Material::getMass(){//returns mass of material
	return mass;
}

double Material::getVolume(){//returns volume of material
	return volume;
}
