#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <utility>
#include "asteroid.hpp"

class Map{
public:
	Map();
	~Map() {};

	void addAsteroid(Asteroid &a, int &x, int &y);

	std::vector<std::pair<int, int>> getCoordinates();

private:
	std::vector<std::vector<Asteroid>> mapData;
	std::vector<std::pair<int, int>> coordinates;
}

#endif
