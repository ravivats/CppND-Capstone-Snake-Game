#include "object.h"

#include <cmath>
#include <iostream>

// init static object count
int Object::_object_count = 0;

// constructor
Object::Object(int points) : _points(points) {
  _object_count++;
}  // int points and increment object count

int Object::getObjectCount() { return _object_count; }

std::string Object::getObjectColorName() const { return _color_name; }

int Object::getPoints() { return 0; }
