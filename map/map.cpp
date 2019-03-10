#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <utility>
#include "asteroid.hpp"
#include "map.hpp"

Map::Map(){
	for(int  i = 0; i < 10000; i++){
		std::vector<Asteroid> inner(10000);
		mapData.push_back(inner);
	}
}

void Map::addAsteroid(Asteroid &a, int &x, int &y){
	mapData[x][y] = a;
	std::pair <int, int> xy;
	xy.first = x;
	xy.second = y;
	coordinates.push_back(xy);
}

std::vector<std::pair<int, int>> Map::getCoordinates(){
	return coordinates;
}
