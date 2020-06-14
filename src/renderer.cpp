#include "renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

// Destruct renderer
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, Snake const enemy_snake,
                      std::shared_ptr<Food> const &food,
                      std::unique_ptr<Poison> const &poison) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen

  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, food->getColor()[0], food->getColor()[1],
                         food->getColor()[2],
                         0xFF);  // get rgb color from food object
  block.x = food->point.x * block.w;
  block.y = food->point.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render poison
  SDL_SetRenderDrawColor(sdl_renderer, poison->getColor()[0],
                         poison->getColor()[1], poison->getColor()[2],
                         0xFF);  // get rgb color from poison object
  block.x = poison->point.x * block.w;
  block.y = poison->point.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render enemy snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xCC, 0x55, 0x00, 0xFF);  // burnt orange
  for (SDL_Point const &point : enemy_snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render enemy snake's head
  block.x = static_cast<int>(enemy_snake.head_x) * block.w;
  block.y = static_cast<int>(enemy_snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x8B, 0x00, 0xFF, 0xFF);  // violet
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, std::string food_color,
                                 std::string poison_color, int food_points,
                                 int poison_points) {
  std::string title{
      "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) +
      "      Food: " + food_color + "/" + std::to_string(food_points) +
      " Pts: " + "    Poison: " + poison_color + "/" +
      std::to_string(poison_points) +
      " Pts: "};  // updated title to include more info
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
