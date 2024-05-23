#include <queue>

struct SnakePart {
  int x = 0;
  int y = 0;
};

struct SnakeMove {
  int dx = 0;
  int dy = 0;
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
  std::queue<SnakeDirection> _moves;
  SnakeDirection _direction;
  SnakePart *getHead();
  SnakePart *getTail();
public: 
  Snake(int x, int y, int resize);
  static SnakeMove getMove(SnakeDirection direction);
  void step();
  void turn(SnakeDirection direction);
  std::queue<SnakePart> getBody() const;
};
