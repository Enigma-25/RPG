// Include headers
#include "map.hpp"
#include "player.hpp"

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

// Enum Definitions
enum DebugMode { 
  OFF = 0,
  DEBUGON = 1,
  DEBUG_MAP = 2,
  DEBUG_PLAYER = 3,
  DEBUG_ITEM = 4,
  DEBUG_INTERACTION = 5,
  DEBUG_TILE = 6,
  VERBOSE = 7
};
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

// Global Variables
const int DIALOGUE_SIZE = 256;
ostringstream dialogue;
bool quitGame = false;
string mapDirectory = "./mapName/";

// Function Prototypes
void pushd(const std::string& message, const char* speaker = nullptr);
void clear();