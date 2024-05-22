#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/timer.h>

class Game {
private:
  ALLEGRO_TIMER* _timer;
  ALLEGRO_EVENT_QUEUE* _queue;
  ALLEGRO_DISPLAY* _display;
  ALLEGRO_FONT* _font;
  
  void draw();
public:
  Game();
  ~Game();

};

