#include "game.h"

#include <iostream>

#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, grid_width, grid_height),
      enemy_snake(grid_width, grid_height, grid_width / 2,
                  grid_height / 2),  // initialize enemy snake
      food(std::make_shared<Food>(Food::Color::GREEN, 1)),  // initialize food
      poison(std::make_unique<Poison>(Poison::Color::RED,
                                      -1)),  // initialize poison
      engine(dev()),
      random_w(1, static_cast<int>(grid_width - 1)),
      random_h(1, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);

    Update();
    renderer.Render(snake, enemy_snake, food,
                    poison);  // render now includes enemy_snake and poison

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(
          score, frame_count, getObjectColor(*food), getObjectColor(*poison),
          food->getPoints(),
          poison->getPoints());  // more info added to window title
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y, x_w, y_w;

  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // pick x and y coordinate from random numbers in poison_location.txt
    // other alternate approaches can be used
    x_w = poison->positions[random_w(engine) / 8].first;
    y_w = poison->positions[random_w(engine) / 8].second;

    // Check that the location is not occupied by a snake item before placing
    // food and poison.
    if (!snake.SnakeCell(x, y) && !snake.SnakeCell(x_w, y_w)) {
      food->point.x = x;
      food->point.y = y;
      poison->point.x = x_w;
      poison->point.y = y_w;
      enemy_snake.direction = static_cast<Snake::Direction>(
          x /
          8);  // random number to pick enemy snake direction.
               // Can select emum by number/index. Could be improved

      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  enemy_snake.Update();  // update enemy snake

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food->point.x == new_x && food->point.y == new_y) {
    score += food->getPoints();
    // Check for bonus. Could be improved
    if ((score % 3 == 0) && (food->getPoints() == 1)) {
      *food + *food;
    }  // operator overload to add bonus
    else if (food->getPoints() == 1) {
      food->setColor(Food::Color::GREEN);
    }  // no bonus so food color set to green
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    enemy_snake.GrowBody();  // just grow enemy snake, not increase speed
    snake.speed += 0.02;
  }
  // Check if there's poison over here
  if (poison->point.x == new_x && poison->point.y == new_y) {
    score += poison->getPoints();
    // check if score is less than zero
    // means poison made the score negative and snake die
    if (score < 0) {
      snake.alive = false;
    }
    PlaceFood();
  }
  // Check if there's enemy snake over here
  if (enemy_snake.SnakeCell(new_x, new_y)) {
    snake.alive = false;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// templated method to return object color name
template <typename T>
std::string Game::getObjectColor(T &object) {
  return object.getObjectColorName();
}