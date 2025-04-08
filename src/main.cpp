#include "main.hpp"

// Global variable declarations
deque<string> dialogueBuffer;
vector<string> mapList; // List of maps 
string mapName = "mapName";
bool quitGame = false, interactionMode = false, gamePaused = false;
int errorId = 0;
bool debugFlag = false;

void Player::playerInput(Map& map) {
  char cmd;
  cin >> cmd;
  
  string wallBlock = "You can't move there.";
  string boundsBlock = "Going out of bounds isn't allowed.";
  
  Tile* target_tile = nullptr;
  
  switch (cmd) {
    case 'w': 
    if (y > 0) {
      target_tile = &map.mapData[y - 1][x];
      
      if (interactionMode) {
        if (target_tile->hasProperty(interactable)) {
          pushd("You interacted.");
        } else {
          pushd("Nothing to interact with here.");
        }
        interactionMode = false;
        break;
      }
      
      if (!target_tile->hasProperty(solid)) {
        y--;
      } else {
        pushd(wallBlock);
      }
    } else {
      pushd(boundsBlock);
    }
    break;
    
    case 'a':
    if (x > 0) {
      target_tile = &map.mapData[y][x - 1];
      
      if (interactionMode) {
        if (target_tile->hasProperty(interactable)) {
          pushd("You interacted.");
        } else {
          pushd("Nothing to interact with here.");
        }
        interactionMode = false;
        break;
      }
      
      if (!target_tile->hasProperty(solid)) {
        x--;
      } else {
        pushd(wallBlock);
      }
    } else {
      pushd(boundsBlock);
    }
    break;
    
    case 's':
    if (y >= 0 && static_cast<size_t>(y) < map.mapData.size() - 1) {
      target_tile = &map.mapData[y + 1][x];
      
      if (interactionMode) {
        if (target_tile->hasProperty(interactable)) {
          pushd("You interacted.");
        } else {
          pushd("Nothing to interact with here.");
        }
        interactionMode = false;
        break;
      }
      
      if (!target_tile->hasProperty(solid)) {
        y++;
      } else {
        pushd(wallBlock);
      }
    } else {
      pushd(boundsBlock);
    }
    break;
    
    case 'd':
    if (x >= 0 && static_cast<size_t>(x) < map.mapData[y].size() - 1) {
      target_tile = &map.mapData[y][x + 1];
      
      if (interactionMode) {
        if (target_tile->hasProperty(interactable)) {
          pushd("You interacted.");
        } else {
          pushd("Nothing to interact with here.");
        }
        interactionMode = false;
        break;
      }
      
      if (!target_tile->hasProperty(solid)) {
        x++;
      } else {
        pushd(wallBlock);
      }
    } else {
      pushd(boundsBlock);
    }
    break;
    
    case 'e':
    if (interactionMode) {
      if (debugFlag) {
        // Debug menu when in debug mode
        pushd("Debug Menu:\n1. View error log\n2. View player info\n3. View map info\n4. Toggle coordinate display\n5. Exit debug menu\n6. Test dialogue buffer");
        char debug_cmd;
        cin >> debug_cmd;
        switch(debug_cmd) {
          case '1':
            {
              ifstream errorFile("error.log");
              if (errorFile) {
                string line;
                while (getline(errorFile, line)) {
                  pushd(line);
                }
              } else {
                pushError("Debug: Could not open error.log");
                pushd("No error log available");
              }
            }
            break;
          case '2':
            {
              string bufferInfo = "Player Info:\nPosition: (" + to_string(x) + ", " + to_string(y) + 
                                  ")\nCurrent Tile: " + to_string(map.mapData[y][x].tileType) + 
                                  "\nInteraction Mode: " + (interactionMode ? "ON" : "OFF") +
                                  "\nDialogue Buffer: " + to_string(dialogueBuffer.size()) + "/" + 
                                  to_string(maxBufferSize);
              pushd(bufferInfo);
            }
            break;
          case '3':
            pushd("Map Info:\nName: " + mapName + 
                  "\nSize: " + to_string(map.mapData.size()) + "x" + 
                  to_string(map.mapData[0].size()) + 
                  "\nSpawn: (" + to_string(map.spawn[0]) + ", " + 
                  to_string(map.spawn[1]) + ")");
            break;
          case '4':
            debugFlag = !debugFlag;
            pushd("Coordinate display: " + string(debugFlag ? "ON" : "OFF"));
            break;
          case '5':
            break;
          case '6':
            {
              pushd("Test message 1");
              pushd("Test message 2");
              pushd("Test message 3", "Debug");
              pushd("Messages should appear together");
            }
            break;
          default:
            pushd("Invalid debug command");
        }
      } else {
        debugFlag = !debugFlag;
      }
      interactionMode = false;
      break;
    }

    // Validate position before entering interaction mode
    if (y >= 0 && y < static_cast<int>(map.mapData.size()) &&
        x >= 0 && x < static_cast<int>(map.mapData[y].size())) {
      interactionMode = true;
      pushd("Interaction mode: ON");
    } else {
      pushError("Player position out of bounds: (" + to_string(x) + ", " + to_string(y) + ")");
      pushd("Cannot enter interaction mode - invalid position");
    }
    break;

    case 'q':
    pushd("Quitting game...");
    quitGame = true;
    break;

    // Debug command now integrated into debug menu
    case 'x':
    if (debugFlag) {
      pushd("Use 'e' in interaction mode to access debug menu");
    } else {
      pushd("Invalid command");
    }
    break;

    default:
    pushd("Invalid command: '" + string(1, cmd) + "'");
    interactionMode = false; // Reset interaction mode
    break;
  }
}

void setup(Player& player, Map& map) {
  player.x = 22;
  player.y = 1;
  
  map.getMapData(); // Fetch the map data
  map.drawMap(player); // Draw the map with player

  mapList.push_back("mapName2");
  
  pushd("Use WASD to move, Q to quit.");
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

  Player player(0, 0); // Initialize player
  Map map; // Initialize map
  
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