#include "main.hpp"

void clear() { // Clear the console
  cout << "\033[2J\033[1;1H";
}

void pushd(const std::string& message, const char* speaker) {
  ostringstream formattedMessage;
  const char* src = message.c_str();

  while (*src) {
    if (*src == '-' && src[1] == '-') {
      formattedMessage << "\n";  // Handle "--" as newline
      src += 2;  // Skip over "--"
    } else if (*src == '\\' && src[1] == 'n') {
      formattedMessage << "\n";  // Handle "\n" escape sequence as newline
      src += 2;  // Skip over the escape sequence
    } else {
      formattedMessage.put(*src++);  // Add regular character
    }
  }

  if (speaker == nullptr) {
    dialogue << "* \"" << formattedMessage.str() << "\"";  // If no speaker, use "*"
  } else {
    dialogue << speaker << ": \"" << formattedMessage.str() << "\"";  // Include speaker if provided
  }
}

void printd() {
  if (!dialogue.str().empty()) {
    cout << dialogue.str() << endl;
  }
  dialogue.str(""); // Reset the string buffer
  dialogue.clear(); // Clear the internal state of the stream
}

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