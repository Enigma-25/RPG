#include "main.hpp"

// Global variable declarations
deque<string> dialogueBuffer;
vector<string> mapList; // List of maps 
string mapName = "mapName";
bool quitGame = false, interactionMode = false, gamePaused = false;
int errorId = 0;
bool debugFlag = false;

void setup(Player& player, Map& map) {
  player.x = map.spawn[0];
  player.y = map.spawn[1];
  
  map.getMapData(); // Fetch the map data
  map.drawMap(player); // Draw the map with player

  mapList.push_back("mapName2");
  
  pushd("Use WASD to move, Q to quit.");
  pushd("Spawn: " + to_string(map.spawn[0]) + ", " + to_string(map.spawn[1]));
  pushd("Current position: " + to_string(player.x) + ", " + to_string(player.y));
  printd();
}

void gameLoop(Player& player, Map& map) {
  player.playerInput(map); // Pass the map to playerInput
  map.drawMap(player); // Draw map with updated player position
  if (debugFlag) cout << "x:" << player.x << " y: " << player.y << "\n"; // Print player coordinates if debug mode is on
  printd();
}

void pushError(const string& message) {
  // check if `error.log` exists
  ifstream errorFile("error.log");
  if (!errorFile) {
    // Create the file if it doesn't exist
    ofstream newFile("error.log");
    newFile.close();
  }
  ofstream errorLog("error.log", std::ios::app); // Open in append mode
  if (!errorLog) {
    cerr << "Error opening error.log for writing." << endl;
    pushd("Error opening error.log for writing.");
    return;
  }
  
  // Write the error message to the log
  cerr << message << endl;
  errorLog << errorId << "| " << message << endl;
  errorId++;
  errorLog.close();
}

int main(int argc, char* argv[]) {
  // Initialize mapList with default map
  mapList.push_back("mapName");

  if (argc > 1) {
    mapList[0] = argv[1]; // Get the map name from command line argument
  } else if (argc > 2) {
    cerr << "Error: Too many arguments provided." << endl;
    return 1;
  }

  mapName = mapList[0]; // Set the map name

  Map map; // Initialize map
  map.getMapData(); // Get map data first to have spawn coordinates
  Player player(map.spawn[0], map.spawn[1]); // Initialize player at spawn position
  
  setup(player, map); // Set up the game with player and map
  
  while (!quitGame) {
    if (!gamePaused) gameLoop(player, map); // Run the game loop
    // else (to be added)
  }
  
  clear();
  pushd("Bye, see ya' later... or not. Preferably not.");
  printd();
  
  return 0;
}