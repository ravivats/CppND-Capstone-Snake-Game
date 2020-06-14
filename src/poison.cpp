
#include "poison.h"

#include <cmath>
#include <fstream>
#include <iostream>

// constructor
Poison::Poison(Color color, int points)
    : Object(points)  // call object constructor
{
  setColor(color);
  std::ifstream infile(
      "../src/poison_location.txt");  // read poison locations from file
                                      // poison_location.txt
  int x, y;
  while (infile >> x >> y) {
    positions.push_back(std::pair<int, int>(
        x, y));  // store xy positions from file in a vector of pairs
  }
}

// getter/ setters
void Poison::setColor(Color color) {
  switch (color) {
    case (Color::RED):
      _rgb = _red_rgb;
      _color_name = "Red";
      break;
    case (Color::GREEN):
      _rgb = _green_rgb;
      _color_name = "Green";
      break;
    case (Color::BLUE):
      _rgb = _blue_rgb;
      _color_name = "Blue";
  }
}

void Poison::setColor(int red, int green, int blue, std::string color_name) {
  _rgb[0] = red;
  _rgb[1] = green;
  _rgb[2] = blue;
  _color_name = color_name;
}

std::vector<int> Poison::getColor() const { return _rgb; }

void Poison::setPoints(int points) { _points = points; }

int Poison::getPoints() { return _points; }
