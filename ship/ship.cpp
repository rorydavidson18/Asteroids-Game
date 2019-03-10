#include <iostream> //may need more includes, but this is the basics
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "ship.hpp"
#include "../asteroids/asteroid.hpp"
#include "../materials/allMaterials.hpp"

using namespace std;

Ship::Ship() { //default constructor
    direction.push_back(0);  //vector of the direction/magnitude of the ship
    direction.push_back(0); //2nd vector component
    position.push_back(520);
    position.push_back(280);
    velocity = 0.0;  //velocity of the ship is 0
    acceleration = 0.0; //acceleration of the ship is 0
    magnitude = 0.0; //magnitude of the ship is 0
    ship_sprite_sheet = "ship/shipsheetparts.PNG";
    damage = 0; // ship damage state
}

void Ship::retrieveMaterial(Asteroid current_asteroid) { //retrieves the Material from the Asteroid
    materials.push_back(current_asteroid.getMaterial());  //getMaterial function returns the Material object that is on that asteroid
}

void Ship::moveForward() { //updates the ship position vector to move forward
    direction[1]+=1;  //substract one because the ship will be facing up and 0,0 is the top left so when you move forward you want the y position to get smaller
}

void Ship::moveRight() { //update ship position vector to move right
    position[0]+=1;
}

void Ship::moveLeft() { //update ship position vector to move left
    position[0]-=1;
}

void Ship::moveBackward() { //updates ship position vector to move backward
    position[1]-=1;
}

void Ship::calculateMagnitude() {  //calculates the magnitude of the ship vector
    magnitude = sqrt(pow(direction[0], 2)+pow(direction[1], 2));
}

double Ship::getValue() { //returns value of all materials on the ship
    double value = 0;
    int size = materials.size();
    for (int i=0; i<size; i++) {
        value += materials.at(i).getPrice();  // may need to change getPrice part depending on the name of the function in the asteroid class
    }
    return value;
}

string Ship::getStringMaterials() {  //returns vector of all materials on the ship
    std::string str;
    int size = materials.size();
    for(int i = 0; i<size; i++){
        string item = typeid(materials.at(i)).name();
        str += item;
        str += ',';
    }
    str.pop_back();
    return str;
}

vector<Material> Ship::getVectorMaterials() {  //return the vector of materials
    return materials;
}

double Ship::getVelocity() {  //returns the velocity of the ship
    return velocity;
}

double Ship::getAcceleration() {  //returns the acceleration of the ship
    return acceleration;
}

double Ship::getMagnitude() {  //returns the magnitude of the ship
    return magnitude;
}

void Ship::setPosition(int x, int y) {
    position[0] = x;
    position[1] = y;
}

int Ship::getXPosition() {
    return position[0];
}

int Ship::getYPosition() {
    return position[1];
}

string Ship::getSpriteSheetPath() {
    return ship_sprite_sheet;
}

bool Ship::isShipSafe() {
    if(damage < 50) {
        return true;
    } else {
        return false;
    }
}

