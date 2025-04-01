#ifndef PLAYER_HPP
#define PLAYER_HPP

class Map; // Forward declaration

class Player {
public:
  int x, y; // Player position
  Player(int startX, int startY) : x(startX), y(startY) {}

  void playerInput(Map& map); // Now playerInput is a method of the Player class
};

#endif // PLAYER_HPP