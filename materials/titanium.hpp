#ifndef TITANIUM_HPP_
#define TITANIUM_HPP_

#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"

// note: no need to recreate methods that are inherited from materials (Andrew)

class Titanium : public Material{//same as material c++ files, but
public:				//inheriting from base class
	Titanium();

	~Titanium() {};
};

#endif
