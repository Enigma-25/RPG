#include "main.hpp"

ostringstream dialogue; // Global variable for dialogue
string mapDirectory = "./mapName/";
bool quitGame = false;

void setup(Player& player, Map& map) {
  player.x = 22;
  player.y = 1;

  map.getMapData(); // Fetch the map data
  map.drawMap(player); // Draw the map with player

  pushd("Use WASD to move, Q to quit.");
  printd();
}

void gameLoop(Player& player, Map& map) {
  player.playerInput(map); // Pass the map to playerInput
  map.drawMap(player); // Draw map with updated player position
  printd();
}

int main() {
  Player player(0, 0); // Initialize player
  Map map; // Initialize map

  setup(player, map); // Set up the game with player and map

  while (!quitGame) {
    gameLoop(player, map); // Run the game loop
  }
  
  clear();
  pushd("Bye, see ya' later... or not. Preferably not.");
  printd();
  
  return 0;
}