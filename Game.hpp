#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_image.h>

#include "Snake.hpp"

class Game {
private:
  ALLEGRO_TIMER* _timer;
  ALLEGRO_EVENT_QUEUE* _queue;
  ALLEGRO_DISPLAY* _display;
  ALLEGRO_FONT* _font;

  ALLEGRO_BITMAP* _gameBuffer;

  unsigned _frameCounter = 0;

  Snake snake = Snake(10,10,20, SNAKE_DOWN);

  const unsigned BUFFER_W = 200;
  const unsigned BUFFER_H = 150;
  const unsigned WINDOW_SCALE = 4;

  bool _needsRedraw = false;
  bool _exit = false;
  
  void draw();
  void update();
  void onKeyDown(ALLEGRO_KEYBOARD_EVENT event);
public:
  Game();
  ~Game();

};

