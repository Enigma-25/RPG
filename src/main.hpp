#ifndef MAIN_HPP
#define MAIN_HPP

// Include headers
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdarg>
#include <deque>  // Add for dialogue buffer

// Using directives
using std::cout;
using std::cin;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::ostringstream;
using std::istringstream;
using std::deque; // Add deque

// Enum Definitions
enum TileProperties {
  solid,
  interactable,
  has_item
};

enum TileType { 
  EMPTY = 0, 
  WALL = 1, 
  CHAIR = 2, 
  VERTICAL_DOOR = 3, 
  HORIZONTAL_DOOR = 4, 
  TABLE = 5, 
  LEFT_PANEL = 6, 
  RIGHT_PANEL = 7
};

struct Tile {
  TileType tileType = EMPTY;
  int specialID = -1;
  bool properties[3] = {false, false, false}; // solid, interactable, has_item
  
  bool hasProperty(TileProperties prop) const {
    return properties[prop];
  }
  
  void setProperty(TileProperties prop, bool value = true) {
    properties[prop] = value;
  }
};

// Class Declarations
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
  void readMapSection(ifstream& mapFile, string& line, string& mapDataSection, int spawn[2]); // Read map section
  void readSpecialSection(ifstream& mapFile, string& line); // Read special section
  int spawn[2]; // Starting position
  string getDebugInfo() const; // Add debug info method
};

// Global Variables
const int DIALOGUE_SIZE = 256;
const size_t maxBufferSize = 5; // Move constant here
extern std::deque<std::string> dialogueBuffer;
extern bool quitGame, interactionMode, gamePaused;
extern string mapName;
extern vector<string> mapList;
int errorId = 0;
bool debugFlag = false;

// Function Prototypes
void pushd(const string& message, const char* speaker = nullptr);
void printd();
void clear();
void pushError(const string& message);
void logCommand(const string& cmd, const Player& player);
string getTileDebugInfo(const Tile& tile);

#endif // MAIN_HPP