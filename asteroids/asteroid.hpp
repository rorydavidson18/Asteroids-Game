#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_
#include "../materials/allMaterials.hpp"
#include <iostream>
#include <string>
#include <vector>

class Asteroid {
  public:
  	Asteroid();
  	~Asteroid() {};
  	double getMass();
  	std::vector<int> getPosition();
  	std::vector<double> getVelocity();
    double getVolume();
    std::string getName();
    Material getMaterial();
    std::string getMaterialType();
    void setMass(double m);
    void setPosition(std::vector<int> p); // set position to coords (x,y)
    void setVelocity(std::vector<double> v); // sets velocity in x and y directions
    void setVolume(double vol);
    void setName(std::string nm);
    void setMaterial(Material m);
    void setNumber(int n);
    int getNumber();

  protected:
    int number;
    std::string name; // name of asteroid
    std::string spriteSheet; // filename for sprite sheet
  	double mass;
    std::vector<int> position; // 2D vector for position
    double volume;
    std::vector<double> velocity; // 2D vector of velocity
    Material primaryMaterial; // asteroids primary material
};

#endif
