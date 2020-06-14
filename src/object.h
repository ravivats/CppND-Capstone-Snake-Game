#ifndef OBJECT_H
#define OBJECT_H

#include <future>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "SDL.h"

class Object {
 public:
  // enum
  enum class Color { RED, GREEN, BLUE };  // enum for pre set colors

  // constructor
  Object(int points);

  // variables
  SDL_Point point;  // SDL point

  // functions
  static int getObjectCount();  //  returns number of objects created
  std::string getObjectColorName() const;

  // setter/getters for typical behaviour
  virtual void setColor(Color color) = 0;  // pure virtual function must be
                                           // implement in derived class
  virtual void setColor(
      int red, int green, int blue,
      std::string color_name) = 0;  // pure virtual function must be implement
                                    // in derived class
  virtual std::vector<int> getColor()
      const = 0;  // pure virtual function must be implement in derived class
  virtual void setPoints(int points) = 0;  // pure virtual function must be
                                           // implement in derived class
  virtual int
  getPoints();  // virtual function can be overriden in a derived class

 protected:
  std::vector<int> _rgb{0, 0, 0};  // vector to store object rgb color
  const std::vector<int> _red_rgb{255, 0, 0};    // red
  const std::vector<int> _green_rgb{0, 255, 0};  // green
  const std::vector<int> _blue_rgb{0, 0, 255};   // blue
  int _points;                                   // object points to +/- score
  std::string _color_name;  // string for color name to display in title window

 private:
  static int
      _object_count;  // static int to count the number of objects created
};

#endif
