#ifndef GAME_H
#define GAME_H

#include <future>
#include <mutex>
#include <random>
#include <thread>

#include "SDL.h"
#include "controller.h"
#include "food.h"
#include "poison.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Snake enemy_snake;               // enemy snake
  std::shared_ptr<Food> food;      // shared pointer for object food
  std::unique_ptr<Poison> poison;  // unique pointer for object poison

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};  // init score

  void PlaceFood();
  void Update();
  template <typename T>
  std::string getObjectColor(
      T &object);  // templated method to return object color name
};

#endif
