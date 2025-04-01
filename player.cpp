#include "main.hpp"

void Player::playerInput(Map& map) {
  char cmd;
  cin >> cmd;
  
  Tile target;
  
  switch (cmd) {
    case 'w': 
    if (y > 0) { // Check if the player isn't at the top edge
      target = map.mapData[y - 1][x]; // Tile above
      if (target != WALL) { // If tile above is not a wall, move
        y--;
      } else {
        pushd("You can't go through walls.");
      }
    } else {
      pushd("Going out of bounds isn't allowed.");
    }
    break;
    
    case 'a':
    if (x > 0) { // Check if the player isn't at the left edge
      target = map.mapData[y][x - 1]; // Tile to the left
      if (target != WALL) { // If tile to left is not a wall, move
        x--;
      } else {
        pushd("You can't go through walls.");
      }
    } else {
      pushd("Going out of bounds isn't allowed.");
    }
    break;
    
    case 's':
    if (y < map.mapData.size() - 1) { // Check if the player isn't at the bottom edge
      target = map.mapData[y + 1][x]; // Tile below
      if (target != WALL) { // If tile below is not a wall, move
        y++;
      } else {
        pushd("You can't go through walls.");
      }
    } else {
      pushd("Going out of bounds isn't allowed.");
    }
    break;
    
    case 'd':
    if (x < map.mapData[y].size() - 1) { // Check if the player isn't at the right edge
      target = map.mapData[y][x + 1]; // Tile to the right
      if (target != WALL) { // If tile to right is not a wall, move
        x++;
      } else {
        pushd("You can't go through walls.");
      }
    } else {
      pushd("Going out of bounds isn't allowed.");
    }
    break;
    
    case 'e':
    pushd("Interaction hasn't been implemented yet.");
    break;
    
    case 'q':
    quitGame = true; // Set the quit flag;
    break;
    
    default:
    pushd("Invalid command.");
    break;
  }
}