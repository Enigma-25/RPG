// Include headers
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdarg>

// Using directives
using std::cout;
using std::cin;
using std::cerr;
using std::ifstream;
using std::endl;
using std::string;
using std::vector;
using std::ostringstream;
using std::istringstream;

// Global Variables
const int DIALOGUE_SIZE = 256;
ostringstream dialogue;
bool quitGame = false;

// Function Prototypes
void pushd(const std::string& message, const char* speaker = nullptr);
void clear();

// Enum Definitions
enum TileProperties {solid, interactable, has_item};
enum Tile { 
  EMPTY = 0, 
  WALL = 1, 
  CHAIR = 2, 
  VERTICAL_DOOR = 3, 
  HORIZONTAL_DOOR = 4, 
  TABLE = 5, 
  LEFT_PANEL = 6, 
  RIGHT_PANEL = 7
};

// Classes
class Map; // Forward declaration

class Player {
public:
  int x, y; // Player position
  Player(int startX, int startY) : x(startX), y(startY) {}

  void playerInput(Map& map); // Now playerInput is a method of the Player class
};

class Map {
public:
  vector<vector<Tile>> mapData; // Map data
  void drawMap(const Player& player); // Draw the map
  void getMapData(); // Fetch map data from file
};

void Map::drawMap(const Player& player) {
  clear(); // Clear the console before drawing the map
  for (int row = 0; row < mapData.size(); ++row) {
    for (int col = 0; col < mapData[row].size(); ++col) {
      if (row == player.y && col == player.x) {
        cout << "Ｏ"; // Draw player
      } else {
        switch (mapData[row][col]) {
          case EMPTY: cout << "　"; break; // Space
          case WALL: cout << "Ｈ"; break; // Wall
          case CHAIR: cout << "＃"; break; // Chair
          case VERTICAL_DOOR: cout << "｜"; break; // Vertical Door
          case HORIZONTAL_DOOR: cout << "－"; break; // Horizontal Door
          case TABLE: cout << "＝"; break; // Table/Counter/Bar/Desk
          case LEFT_PANEL: cout << "［"; break; // Left-facing panel
          case RIGHT_PANEL: cout << "］"; break; // Right-facing panel
        }
      }
    }
    cout << endl;
  }
}

void Map::getMapData() {
  mapData.clear(); // Clear existing map data to avoid appending to old data
  
  ifstream mapFile("map.cmap");
  if (!mapFile.is_open()) {
    cerr << "Failed to open map file (map.cmap)\n"; 
    return;
  }
  
  string line;
  string mapSection;
  
  // Find the [MAP] section
  while (getline(mapFile, line)) {
    if (line == "[MAP]") break;
  }
  
  // Read the entire [MAP] section as a single string
  while (getline(mapFile, line)) {
    if (line.empty() || line[0] == '[') break; // Stop at the next section or empty line
    mapSection += line + " ";
  }
  
  // Split the mapSection string into rows based on spaces
  istringstream mapStream(mapSection);
  string row;
  while (mapStream >> row) {
    vector<Tile> rowData;
    for (char c : row) {
      if (c >= '0' && c <= '9') {
        // Convert numeric characters to enum values
        rowData.push_back(static_cast<Tile>(c - '0'));
      }
    }
    mapData.push_back(rowData);
  }
}

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