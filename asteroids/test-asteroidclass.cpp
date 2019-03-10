#include <iostream>
#include <string>
#include <vector>
#include "asteroid.hpp"
#include "../materials/allMaterials.hpp"
using namespace std;

int main(){
  Asteroid a;
  vector<int> pos;
  pos.push_back(10);
  pos.push_back(11);
  vector<double> vel;
  vel.push_back(1.2);
  vel.push_back(3.4);

  // testing setters and getters
  a.setMass(3.141);
  a.setPosition(pos);
  a.setVelocity(vel);
  a.setVolume(1000.3);
  a.setName("HQ23T");

  cout << "Mass of asteroid: " << a.getMass() << endl;
  pos = a.getPosition();
  cout << "Position of asteroid: " << pos[0] << ", " << pos[1] << endl;
  vel = a.getVelocity();
  cout << "Velocity of asteroid: " << vel[0] << ", " << vel[1] << endl;
  cout << "Volume of asteroid: " << a.getVolume() << endl;
  cout << "Name of asteroid: " << a.getName() << endl;
  Material m = a.getMaterial();
  cout << "Primary material of asteroid: " << m.getForm() << endl;

  Gold g;
  a.setMaterial(g);
  m = a.getMaterial();
  cout << "Setting to gold: " << endl;
  cout << "Primary material of asteroid: " << m.getForm() << endl;


	return 0;
}
