#include "main.hpp"

// Global variable declarations
deque<string> dialogueBuffer;
vector<string> mapList; // List of maps 
string mapName = "mapName";
bool quitGame = false, interactionMode = false, gamePaused = false;

void Map::drawMap(const Player& player) {
  clear(); // Clear the console before drawing the map
  for (int row = 0; row < static_cast<int>(mapData.size()); ++row) {
    for (int col = 0; col < static_cast<int>(mapData[row].size()); ++col) {
      if (row == player.y && col == player.x) {
        cout << "Ｏ"; // Draw player
        continue;
      }
      switch (mapData[row][col].tileType) {
        case EMPTY:           cout << "　"; break; // Space
        case WALL:            cout << "Ｈ"; break; // Wall
        case CHAIR:           cout << "＃"; break; // Chair
        case VERTICAL_DOOR:   cout << "｜"; break; // Vertical Door
        case HORIZONTAL_DOOR: cout << "＿"; break; // Horizontal Door
        case TABLE:           cout << "＝"; break; // Table/Counter/Bar/Desk
        case LEFT_PANEL:      cout << "［"; break; // Left-facing panel
        case RIGHT_PANEL:     cout << "］"; break; // Right-facing panel
        default:              cout << "？"; break; // Unknown tile
      }
    }
    cout << endl;
  }
}

void Map::getMapData() {
  mapData.clear(); // Clear existing map data to avoid appending to old data
  spawn[0] = 0, spawn[1] = 0;  // Set spawn position
  
  string mapPath = "maps/" + mapName + "/map.cmap";

  ifstream mapFile(mapPath);
  if (!mapFile.is_open()) {
    pushError("Failed to open map: " + mapName + " from " + mapPath); return; // This will be changed to use a default map
  }
  
  string line, mapDataSection;
  
  // Find the [MAP] section
  while (getline(mapFile, line)) {
    if (line == "[MAP]") { readMapSection(mapFile, line, mapDataSection, spawn); break; }
    
    if (line == "[SPECIAL]") { readSpecialSection(mapFile, line); break; }
    
    // Skip empty and comment lines
    if (line.empty() || line[0] == '#') { continue; }

    // Stop reading
    if (line == "[EOF]") { break; }
    
  }
  mapFile.close(); // Close the file
}

void Map::readSpecialSection(ifstream& mapFile, string& line) {
  // Handle special ID section
  while (getline(mapFile, line)) {
    if (line.empty() || line[0] == '[') break; // Stop at the next section or empty line
    
    // Parse Special section format: "x,y:id"
    istringstream specialStream(line);
    size_t x, y;
    int id;
    
    // Read the x coordinate
    if (!(specialStream >> x)) {
      pushError("Error: Invalid x coordinate in special section");
      continue;
    }
    
    // Expect a comma
    if (specialStream.get() != ',') {
      pushError("Error: Expected ',' in special section");
      continue;
    }
    
    // Read the y coordinate
    if (!(specialStream >> y)) {
      pushError("Error: Invalid y coordinate in special section");
      continue;
    }
    
    // Expect a colon
    if (specialStream.get() != ':') {
      pushError("Error: Expected ':' in special section");
      continue;
    }
    
    // Read the special ID
    if (!(specialStream >> id)) {
      pushError("Error: Invalid Special ID in special section");
      continue;
    }
    
    // Ensure coordinates are within map bounds
    if (y < mapData.size() && x < mapData[y].size()) {
      // Assign the special ID to the correct position in the map data
      mapData[y][x].specialID = id;
    } else {
      pushError("Error: Special ID coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ") with ID " + to_string(id) + " because of " + to_string(mapData.size()) + " rows and " + to_string(mapData[y].size()) + " columns.");
    }
  }
}

void Map::readMapSection(ifstream& mapFile, string& line, string& mapDataSection, int spawn[2]) {
  // Read the entire [MAP] section as a single string
  while (getline(mapFile, line)) {
    if (line.empty() || line[0] == '[') break; // Stop at the next section or empty line
    mapDataSection += line + " ";
  }
  
  // Split the mapSection string into rows based on spaces
  istringstream mapStream(mapDataSection);
  string row;
  while (mapStream >> row) {
    vector<Tile> rowData; // Vector to store Tile for the row
    
    for (char c : row) {
      Tile tile; // Create a new Tile entry
      
      if (c == 'X') {
        // Set spawn position to position of 'X'
        spawn[0] = rowData.size(); // X position
        spawn[1] = mapData.size(); // Y position
      }
      
      if (c >= '0' && c <= '9') {
        tile.tileType = static_cast<TileType>(c - '0');  // Set the Tile type based on the character
        
        // Set properties based on tile type
        switch (tile.tileType) {
        case TABLE:         // tile.setProperty(interactable);  // Not yet
        case WALL:          tile.setProperty(solid);        break;
        case CHAIR:
        case VERTICAL_DOOR:
        case HORIZONTAL_DOOR:
        case LEFT_PANEL:
        case RIGHT_PANEL:   tile.setProperty(interactable); break;
        default: break;
        }
      }
      
      tile.specialID = -1; // Default to no Special ID initially (you'll modify this later)
      
      rowData.push_back(tile); // Push the Tile to the row
    }
    mapData.push_back(rowData); // Add the row to mapData
  }
}

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
  
  string finalMessage = speaker == nullptr ? 
    "* \"" + formattedMessage.str() + "\"" :
    string(speaker) + ": \"" + formattedMessage.str() + "\"";

  dialogueBuffer.push_back(finalMessage);
  
  // Keep buffer size under limit
  while (dialogueBuffer.size() > maxBufferSize) {
    dialogueBuffer.pop_front();
  }
}

void printd() {
  if (!dialogueBuffer.empty()) {
    for (const auto& msg : dialogueBuffer) {
      cout << msg << endl;
    }
    dialogueBuffer.clear(); // Clear after printing
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