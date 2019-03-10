#ifndef SILVER_HPP_
#define SILVER_HPP_

#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"

// note: no need to recreate methods that are inherited from materials (Andrew)

class Silver : public Material{//same as material c++ files, but
public:				//inheriting from base class
	Silver();

	~Silver() {};
};

#endif
