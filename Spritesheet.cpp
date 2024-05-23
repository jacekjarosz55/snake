#include "Spritesheet.hpp"
#include "InitializationException.hpp"

#include <allegro5/bitmap.h>
#include <allegro5/bitmap_io.h>
#include <string>

Spritesheet::Spritesheet(const char *filename) {
  _source = al_load_bitmap(filename);
  if (!_source) {
    throw InitializationException("spritesheet image");
  }
  _spritesX = al_get_bitmap_width(_source) / SPRITESHEET_RES;
  _spritesY = al_get_bitmap_height(_source) / SPRITESHEET_RES;
  for (int y = 0; y <  _spritesY; y++) {
    for (int x = 0; x <  _spritesX; x++) {
      ALLEGRO_BITMAP *spriteBitmap = al_create_sub_bitmap(_source, x*SPRITESHEET_RES, y*SPRITESHEET_RES, SPRITESHEET_RES, SPRITESHEET_RES);
      if (!spriteBitmap) {
        throw InitializationException("spritesheet slice");
      }
      _sprites.push_back(spriteBitmap);
    }
  }
}


Spritesheet::~Spritesheet() {
  for (auto spriteBitmap : _sprites) {
    al_destroy_bitmap(spriteBitmap);
  }
  al_destroy_bitmap(_source);
}


ALLEGRO_BITMAP *Spritesheet::get(unsigned idx) {
  return _sprites.at(idx);
}
