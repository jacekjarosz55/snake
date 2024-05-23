#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
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

  _timer = al_create_timer(1.0 / 30.0); // 30fps
  if (!_timer) {
    throw InitializationException("timer");
  }

  _queue = al_create_event_queue();
  if (!_queue) {
    throw InitializationException("event queue");
  }
  
  
  _gameBuffer = al_create_bitmap(BUFFER_W, BUFFER_H);

  _display = al_create_display(BUFFER_W*WINDOW_SCALE, BUFFER_H*WINDOW_SCALE);
  if (!_display) {
    throw InitializationException("display");
  }

  _font = al_create_builtin_font();
  if (!_font) {
    throw InitializationException("font");
  }

  // listen to keyboard events
  al_register_event_source(_queue, al_get_keyboard_event_source());
  al_register_event_source(_queue, al_get_display_event_source(_display));
  al_register_event_source(_queue, al_get_timer_event_source(_timer));


  // game loop
  // could be split into a separate method
  ALLEGRO_EVENT event;
  al_start_timer(_timer);
  _needsRedraw = false; 
  _exit = false; 
  while (true) {
    al_wait_for_event(_queue, &event);

    switch(event.type) {
      case ALLEGRO_EVENT_KEY_DOWN:
        onKeyDown(event.keyboard);
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        _exit = true;
        break;
      case ALLEGRO_EVENT_TIMER:
        update();
        _needsRedraw = true;
        break;
    }

    if(_exit) {
      break;
    }

    if (_needsRedraw && al_is_event_queue_empty(_queue)) {
      draw();
      _needsRedraw = false;
    }

  }
}

void Game::update() {
  _frameCounter++;
  // TODO: replace '4' with snake speed
  if (_frameCounter % 4 == 0) {
    snake.step();
    if (snake.hasCollidedWithSelf()) {
      _exit = true;
    }
  }
}

// kinda weird but this is the only input we need so
void Game::onKeyDown(ALLEGRO_KEYBOARD_EVENT event) {
  if (event.keycode == ALLEGRO_KEY_ESCAPE) {
    _exit = true;
  }

  if (event.keycode == ALLEGRO_KEY_LEFT) {
    snake.turn(SNAKE_LEFT);
  }
  if (event.keycode == ALLEGRO_KEY_RIGHT) {
    snake.turn(SNAKE_RIGHT);
  }
  if (event.keycode == ALLEGRO_KEY_UP) {
    snake.turn(SNAKE_UP);
  }
  if (event.keycode == ALLEGRO_KEY_DOWN) {
    snake.turn(SNAKE_DOWN);
  }
}

void Game::draw() {
  // draw on the game buffer
  al_set_target_bitmap(_gameBuffer); 
  al_clear_to_color(al_map_rgb(0,0,0));

  for (auto snakePart : snake.getBody()) {
    al_draw_pixel(snakePart.x, snakePart.y, al_map_rgb(0,255,0));
  }

  // draw the buffer onto the window
  al_set_target_backbuffer(_display); 
  al_draw_scaled_bitmap(_gameBuffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, BUFFER_W * WINDOW_SCALE, BUFFER_H * WINDOW_SCALE, 0);
  al_flip_display();
}

Game::~Game() {
  al_destroy_font(_font);
  al_destroy_bitmap(_gameBuffer);
  al_destroy_display(_display);
  al_destroy_timer(_timer);
  al_destroy_event_queue(_queue);
}







