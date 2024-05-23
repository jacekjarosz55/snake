#pragma once

#include <allegro5/bitmap.h>
#include <string>
#include <vector>

class Spritesheet {
private:
  const unsigned SPRITESHEET_RES = 32;
  ALLEGRO_BITMAP *_source;
  unsigned _spritesX;
  unsigned _spritesY;
  unsigned _spriteCount;
  std::vector<ALLEGRO_BITMAP *> _sprites;
public:
  Spritesheet(const std::string& filename);
  ~Spritesheet();
  ALLEGRO_BITMAP *sprite(unsigned idx);
};
