#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <iostream>//may need more includes, but this is the basics
#include <string>

class Material{//header class for materials
public:
	Material();//default constructor

	~Material() {};//destructor

	std::string getColor();//returns color of material

	std::string getUses();//returns uses of material

	std::string getState();//returns matter state of material

	std::string getForm();//returns chemical formula of material

	std::string summary();

	double getPrice();//returns price of material

	int getMass();//returns mass of material
	
	double getVolume();//returns volume of material

protected:
	std::string color, uses, state, form;//color, uses, matter state,
	int mass;	       	             //chemical formula, price,
	double price, volume;                //mass and volume.
};					     

#endif
