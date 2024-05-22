#include "Snake.hpp"

void Snake::move() {
  int dx, dy;
  switch (_direction) {
    case LEFT:
      dx=-1;
      dy=0;
      break;
    case RIGHT:
      dx=1;
      dy=0;
      break;
    case UP:
      dx=0;
      dy=-1;
      break;
    case DOWN:
      dx=0;
      dy=1;
      break;
  }
  
  SnakePart *head = getHead();
  SnakePart newHead;
  newHead.x = head->x + dx;
  newHead.y = head->y + dy;

  // TODO: check colision 

  _body.push(newHead);
  if (_resize > 0) {
    _resize--;
  } else {
    _body.pop();
  }
}

std::queue<SnakePart> Snake::getBody() const {
  return _body;
}
