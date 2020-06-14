#include <fstream>
#include <iostream>

#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has ended! ｡ﾟ･（>﹏<）･ﾟ｡\n";
  int finalScore = game.GetScore();
  if (finalScore < 0) {
    std::cout << "Eating too much poison killed the snake. (╥_╥)" << "\n";
  }
  std::cout << "Score: " << finalScore << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
