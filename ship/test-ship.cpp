#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "../materials/allMaterials.hpp"
#include "ship.hpp"
#include "../asteroids/asteroid.hpp"
using namespace std;

int main(){
    Ship s;

    cout << "Velocity of ship: " << s.getVelocity() << endl;
    cout << "Acceleration of ship: " << s.getAcceleration() << endl;
    cout << "Magnitude of ship: " << s.getMagnitude() << endl;
    cout << "Materials on the ship: " << s.getStringMaterials() << endl;
    cout << "Position of the ship: " << s.getXPosition() << ", " << s.getYPosition() << endl;

    return 0;
}
