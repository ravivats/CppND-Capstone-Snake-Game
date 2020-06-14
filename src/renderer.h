#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "food.h"
#include "poison.h"
#include "snake.h"

class Renderer {
 public:
  // Constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);

  // Destructor
  ~Renderer();

  void Render(Snake const snake, Snake const enemy_snake,
              std::shared_ptr<Food> const &food,
              std::unique_ptr<Poison> const &poison);
  void UpdateWindowTitle(int score, int fps, std::string food_color,
                         std::string poison_color, int food_points,
                         int poison_points);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
