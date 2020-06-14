#include "food.h"

#include <cmath>
#include <iostream>

// constructor
Food::Food(Color color, int points)
    : Object(points)  // call object constructor
{
  setColor(color);
  _thread = std::thread(
      &Food::timer, this);  // start thread within object call method timer()
}

// destructor
Food::~Food() {
  _thread.detach();  // detach thread before object is destroyed to allow game
                     // to close.
}

void Food::setColor(Color color) {
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

// overloaded method to set custom color to a specific rgb value
void Food::setColor(int red, int green, int blue, std::string color_name) {
  _rgb[0] = red;
  _rgb[1] = green;
  _rgb[2] = blue;
  _color_name = color_name;
}
std::vector<int> Food::getColor() const { return _rgb; }

void Food::setPoints(int points) { _points = points; }

int Food::getPoints() {
  std::lock_guard<std::mutex> uLock(_mutex);  // mutex to guard _points
  return _points;
}

// operator overload
Food& Food::operator+(Food& food) {
  std::lock_guard<std::mutex> uLock(_mutex);  // protect _points when modifying
  this->setColor(255, 255, 0, "Yellow");      // set to custom color
  _points = 10;                               // set _points to 10 for bonus
  return *this;
}

// timer method that decreases points obtained by the bonus. Timer constantly
// runs when food is created
void Food::timer() {
  while (true) {
    // sleep thread for 2 second
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::lock_guard<std::mutex> uLock(
        _mutex);      // protect _points when modifying
    if (_points > 1)  // dont
      _points -= 1;   // decrease points after 2 seconds
  }
}
