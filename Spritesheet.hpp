#pragma once

#include <allegro5/bitmap.h>
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
  Spritesheet(const char *filename);
  ~Spritesheet();
  ALLEGRO_BITMAP *get(unsigned idx);
  unsigned size() const { return _sprites.size(); };
};
