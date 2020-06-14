#ifndef POISON_H
#define POISON_H

#include <vector>

#include "object.h"

class Poison : public Object  // inheritance
{
 public:
  // constructor
  Poison(Color color, int points);

  std::vector<std::pair<int, int>> positions;  // xy positions read from file

  // getter/ setters
  void setColor(Color color);
  void setColor(int red, int green, int blue, std::string color_name);
  std::vector<int> getColor() const;
  void setPoints(int points);
  int getPoints();
};

#endif
