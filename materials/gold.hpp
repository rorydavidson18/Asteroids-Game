#ifndef GOLD_HPP_
#define GOLD_HPP_

#include <iostream>//may need more includes, but this is the basics
#include <string>
#include "material.hpp"

class Gold : public Material{//same as material c++ files, but
public:				//inheriting from base class
	Gold();

	~Gold() {};
};

#endif
