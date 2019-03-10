#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include "asteroid.hpp"
using namespace std;

Asteroid::Asteroid() {
  // for random material:
  /* generate number between 1 and 3: */
  int materialSelect = rand() % 3 + 1;

  name = "Rocky";
  spriteSheet = "defaultAsteroidSprite.gif"; // filename for sprite sheet
  mass = 1000; // 1000 kg (a very small asteroid)
  volume = 1000; // 1000 cubic meters
  vector<double> vel;
  vel.push_back(0);
  vel.push_back(0);
  velocity = vel; // not moving

  Gold g;
  Silver s;
  Titanium t;
  // randomly select a material for this asteroid
  switch(materialSelect) {
    case 1 :
      primaryMaterial = g;
      name = "Gold";
      break;
    case 2 :
      primaryMaterial = s;
      name = "Silver";
      break;
    case 3 :
      primaryMaterial = t;
      name = "Titanium";
      break;
  }
}

double Asteroid::getMass() {
  return mass;
}

vector<int> Asteroid::getPosition() {
  return position;
}

vector<double> Asteroid::getVelocity() {
  return velocity;
}

double Asteroid::getVolume() {
  return volume;
}

string Asteroid::getName() {
  return name;
}

Material Asteroid::getMaterial() {
  return primaryMaterial;
}

void Asteroid::setMass(double m) {
  mass = m;
}

void Asteroid::setPosition(vector<int> p) {
  position = p;
}

void Asteroid::setVelocity(vector<double> v) {
  velocity = v;
}

void Asteroid::setVolume(double vol) {
  volume = vol;
}

void Asteroid::setName(string nm) {
  name = nm;
}

void Asteroid::setMaterial(Material m) {
  primaryMaterial = m;
}

void Asteroid::setNumber(int n) {
  number = n;
}

int Asteroid::getNumber() {
  return number;
}

std::string Asteroid::getMaterialType() {
  return typeid(primaryMaterial).name();
}
