#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <cstdlib>
#include <unistd.h>

#include "Game.hpp"
#include "InitializationException.hpp"

Game::Game() {
  if (!al_init()) {
    throw InitializationException("allegro");
  }
  if (!al_install_keyboard()) {
    throw InitializationException("keyboard");
  }

  if (!al_init_image_addon())
  {
    throw InitializationException("image addon");
  }

  timer = al_create_timer(1.0 / 30.0); // 30fps
  if (!timer) {
    throw InitializationException("timer");
  }

  eventQueue = al_create_event_queue();
  if (!eventQueue) {
    throw InitializationException("event queue");
  }
  
  gameBuffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  display = al_create_display(BUFFER_W*WINDOW_SCALE, BUFFER_H*WINDOW_SCALE);
  if (!display) {
    throw InitializationException("display");
  }

  font = al_create_builtin_font();
  if (!font) {
    throw InitializationException("font");
  }

  spritesheet = new Spritesheet("spritesheet.png", 32);

  // listen to keyboard events
  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_register_event_source(eventQueue, al_get_display_event_source(display));
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));



  // initialize game;

  snake = new Snake(0,0,5, SNAKE_DOWN);
  spawnFruit();

  // game loop
  // could be split into a separate method
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  needsRedraw = false; 
  exit = false; 
  while (true) {
    al_wait_for_event(eventQueue, &event);

    switch(event.type) {
      case ALLEGRO_EVENT_KEY_DOWN:
        onKeyDown(event.keyboard);
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        exit = true;
        break;
      case ALLEGRO_EVENT_TIMER:
        update();
        needsRedraw = true;
        break;
    }

    if(exit) {
      break;
    }

    if (needsRedraw && al_is_event_queue_empty(eventQueue)) {
      draw();
      needsRedraw = false;
    }

  }
}

void Game::update() {
  frameCounter++;
  // TODO: replace '4' with snake speed
  if (frameCounter % 4 == 0) {

    snake->step();
    auto head = snake->getHead();
    if (snake->hasCollidedWithSelf() || 
      head.x < 0 || head.x >= TILES_X || head.y < 0 || head.y >= TILES_Y) {
      exit = true;
    }

    for (auto fruitIt = fruits.begin(); fruitIt != fruits.end();) {
      if(snake->hasCollidedWith(*fruitIt)) {
        fruits.erase(fruitIt);
        snake->addLength(1);
        spawnFruit();
      } else {
        ++fruitIt;
      }
    }

  }
}

// kinda weird but this is the only input we need so
void Game::onKeyDown(ALLEGRO_KEYBOARD_EVENT event) {
  if (event.keycode == ALLEGRO_KEY_ESCAPE) {
    exit = true;
  }

  if (event.keycode == ALLEGRO_KEY_LEFT) {
    snake->turn(SNAKE_LEFT);
  }
  if (event.keycode == ALLEGRO_KEY_RIGHT) {
    snake->turn(SNAKE_RIGHT);
  }
  if (event.keycode == ALLEGRO_KEY_UP) {
    snake->turn(SNAKE_UP);
  }
  if (event.keycode == ALLEGRO_KEY_DOWN) {
    snake->turn(SNAKE_DOWN);
  }
}



void Game::draw() {
  // draw on the game buffer
  al_set_target_bitmap(gameBuffer); 
  al_clear_to_color(al_map_rgb(0,0,0));

  drawFruits();
  drawSnake();
  



  // draw the buffer onto the window
  al_set_target_backbuffer(display); 
  al_draw_scaled_bitmap(gameBuffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, BUFFER_W * WINDOW_SCALE, BUFFER_H * WINDOW_SCALE, 0);
  al_flip_display();
}

void Game::drawSnake() {
  const float PI = 3.14;
  float halfsize = (float)TILE_SIZE/2;
  float turn = 0;
  switch(snake->getDirection()) {
  case SNAKE_LEFT:
    turn = 0 * PI;
    break;
  case SNAKE_RIGHT:
    turn = 1 * PI;
    break;
  case SNAKE_UP:
    turn = 0.5 * PI;
    break;
  case SNAKE_DOWN:
    turn = 1.5 * PI;
    break;
  }

  auto snakeBody = snake->getBody();
  auto head = snakeBody.back();
  // draw head
  al_draw_rotated_bitmap(
    spritesheet->get(0),
    halfsize, halfsize,
    head.x*TILE_SIZE + halfsize,
    head.y*TILE_SIZE + halfsize,
    turn,
    0);
  // draw the rest
  for (int i = 0; i < snakeBody.size() - 1; i++) {
    auto snakePart = snakeBody[i];
    al_draw_bitmap(spritesheet->get(1), snakePart.x*TILE_SIZE, snakePart.y*TILE_SIZE, 0);
  }
}


void Game::drawFruits() {
  for (auto fruit : fruits) {
    al_draw_bitmap(spritesheet->get(4), fruit.x*TILE_SIZE, fruit.y*TILE_SIZE, 0);
  }
}


void Game::spawnFruit() {
  Position fruit;
  do {
    fruit.x = rand()%TILES_X;
    fruit.y = rand()%TILES_Y;
  } while (snake->isInside(fruit));
  fruits.push_back(fruit);
}


Game::~Game() {
  delete spritesheet;
  delete snake;
  al_destroy_font(font);
  al_destroy_bitmap(gameBuffer);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(eventQueue);
}
