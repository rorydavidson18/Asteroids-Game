#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <iostream> //may need more includes, but this is the basics
#include <string>
#include <vector>
#include "../asteroids/asteroid.hpp"
#include "../materials/allMaterials.hpp"

using namespace std;

class Ship { //header class for Ships
public:
    Ship(); //default constructor
    
    ~Ship() {}; //destructor
    
    void retrieveMaterial(Asteroid current_asteroid); //retrieves the Material from the Asteroid
    
    void moveForward(); //updates the ship vector to move forward
    
    void moveLeft();  //updates the ship vector to turn left
    
    void moveRight();  //updates the ship vector to turn right
    
    void moveBackward(); //updates the ship position vector to move backwards
    
    void calculateMagnitude();  //calculates the magnitude of the ship vector
    
    double getValue(); //returns value of all materials on the ship
    
    string getStringMaterials();  //returns string of materials on the ship
    
    vector<Material> getVectorMaterials();  //reutrns the vector of Materials
    
    double getVelocity();  //returns the velocity of the ship
    
    double getAcceleration(); //returns the acceleration off the ship
    
    double getMagnitude();  //returns the values of the magnitude
    
    int getXPosition();  //returns integer value of the x position vector
    
    int getYPosition();  //returns the int of the y position vector
    
    void setPosition(int x, int y);
    
    string getSpriteSheetPath(); // returns path to sprite sheet
    
    bool isShipSafe(); // returns true if damage less than 50
    
protected:
    vector<double> direction;  //vector of the direction/magnitude of the ship
    vector<int> position; // vector of position
    vector<Material> materials;  //vector that stores the materials gathered from the asteroids
    int damage; // ship damage state
    double velocity, acceleration, magnitude;  //velocity and acceleration and magnitude of the ship
    string ship_sprite_sheet;
};

#endif

