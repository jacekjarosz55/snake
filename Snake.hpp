#include <queue>

class SnakePart {
public:
  int x = 0;
  int y = 0;
};

enum SnakeDirection {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Snake {
private:
  unsigned _resize = 0;
  std::queue<SnakePart> _body;
  SnakeDirection _direction;
  SnakePart *getHead();
  SnakePart *getTail();
public: 
  void move();
  void setDirection(SnakeDirection dir);
  std::queue<SnakePart> getBody() const;
};
