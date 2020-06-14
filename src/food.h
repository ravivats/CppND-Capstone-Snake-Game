#ifndef FOOD_H
#define FOOD_H

#include <vector>

#include "object.h"

class Food : public Object  // inheritance
{
 public:
  // constructor
  Food(Color color, int points);

  // destructor
  ~Food();

  // getters/setters
  void setColor(Color color);
  void setColor(int red, int green, int blue,
                std::string color_name);  // overloaded method to set custom
                                          // color to a specific rgb value
  std::vector<int> getColor() const;
  void setPoints(int points);
  int getPoints();

  // other
  Food& operator+(Food& food);  // operator + overload
  void timer();  // timer for time penalty that reduces bonus. Timer constantly
                 // runs when food is created

 private:
  std::thread
      _thread;  // holds the thread that has been launched within the object
  std::mutex _mutex;  // mutex protecting _points within object
};

#endif
