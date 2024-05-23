#include "Snake.hpp"

Snake::Snake(int x, int y, int resize) {
  _body.push({x,y});
  _resize = resize;
}


SnakePart *Snake::getHead() {
  return &_body.back();
}

void Snake::turn(SnakeDirection direction) {
  if (
    (_moves.size() == 0 && direction == _direction) 
    || (_moves.back() == direction)) {
    return;
  }
  _moves.push(direction);
}

void Snake::step() {
  SnakePart *head = getHead();
  SnakePart newHead;

  if (_moves.size() > 0) {
    _direction = _moves.front();
    _moves.pop();
  }

  SnakeMove move = getMove(_direction);

  newHead.x = head->x + move.dx;
  newHead.y = head->y + move.dy;

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

