#include "City.h"
#include <iostream>


using namespace std;

//creating city object with attributes: city_name, postion_x, postion_y
City::City(int postion_x, int postion_y, int city_name){
	this->city_name = city_name;
	this->postion_x = postion_x;
	this->postion_y = postion_y;
}
