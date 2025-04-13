#include "main.hpp"

<<<<<<< HEAD
ostringstream dialogue; // Global variable for dialogue
string mapDirectory = "./mapName/";
bool quitGame = false;
bool interactionMode = false;

void Map::drawMap(const Player& player) {
  clear(); // Clear the console before drawing the map
  for (int row = 0; row < mapData.size(); ++row) {
    for (int col = 0; col < mapData[row].size(); ++col) {
      if (row == player.y && col == player.x) {
        cout << "Ｏ"; // Draw player
        continue;
      }
      switch (mapData[row][col].tileType) {
        case EMPTY: cout << "　"; break; // Space
        case WALL: cout << "Ｈ"; break; // Wall
        case CHAIR: cout << "＃"; break; // Chair
        case VERTICAL_DOOR: cout << "｜"; break; // Vertical Door
        case HORIZONTAL_DOOR: cout << "＿"; break; // Horizontal Door
        case TABLE: cout << "＝"; break; // Table/Counter/Bar/Desk
        case LEFT_PANEL: cout << "［"; break; // Left-facing panel
        case RIGHT_PANEL: cout << "］"; break; // Right-facing panel
        default: cout << "？"; break; // Unknown tile
      }
    }
    cout << endl;
  }
}

void Map::getMapData() {
  mapData.clear(); // Clear existing map data to avoid appending to old data
  spawn[0] = 0; spawn[1] = 0;  // Set spawn position
  
  ifstream mapFile(mapDirectory + "map.cmap");
  if (!mapFile.is_open()) {
    pushError("Failed to open map file: " + mapDirectory + "map.cmap");
    return; // This will be changed to use a default map
  }
  
  string line;
  string mapDataSection;
  
  // Find the [MAP] section
  while (getline(mapFile, line)) {
    if (line == "[MAP]") {
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
          
          if (c == 'a') {
            // Set spawn position to position of 'a'
            spawn[0] = rowData.size(); // X position
            spawn[1] = mapData.size(); // Y position
          }
          
          if (c >= '0' && c <= '9') {
            tile.tileType = static_cast<TileType>(c - '0');  // Set the Tile type based on the character
            
            // Set properties based on tile type
            switch (tile.tileType) {
            case WALL:
              tile.setProperty(solid);
              break;
            case CHAIR:
              tile.setProperty(interactable);
              break;
            case TABLE:
              tile.setProperty(solid);
              // tile.setProperty(interactable);  // Not yet
              break;
            case VERTICAL_DOOR:
            case HORIZONTAL_DOOR:
              tile.setProperty(interactable);
              break;
            case LEFT_PANEL:
            case RIGHT_PANEL:
              tile.setProperty(interactable);
              break;
            default:
              break;
            }
          }
          
          tile.specialID = -1; // Default to no Special ID initially (you'll modify this later)
          
          rowData.push_back(tile); // Push the Tile to the row
        }
        mapData.push_back(rowData); // Add the row to mapData
      }
    }
    
    if (line == "[SPECIAL]") {
      // Handle special ID section
      while (getline(mapFile, line)) {
        if (line.empty() || line[0] == '[') break; // Stop at the next section or empty line
        
        // Parse Special section format: "x,y:id"
        istringstream specialStream(line);
        int x, y, id;
        
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
        if (y >= 0 && y < mapData.size() && x >= 0 && x < mapData[y].size()) {
          // Assign the special ID to the correct position in the map data
          mapData[y][x].specialID = id;
        } else {
          pushError("Error: Special ID coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ") with ID " + to_string(id) + " because of " + to_string(mapData.size()) + " rows and " + to_string(mapData[y].size()) + " columns.");
        }
      }
    }
    
    if (line == "[EOF]") {
      break; // Stop reading
    }
    
    if (line.empty() || (line[0] == '/' && line[1] == '/')) {
      continue; // Skip empty lines or lines that start with "//"
    }
  }
  mapFile.close(); // Close the file
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
    if (y < map.mapData.size() - 1) {
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
    if (x < map.mapData[y].size() - 1) {
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
      debugFlag = !debugFlag; // Toggle debug mode
      break;
    }

    interactionMode = true;
    break;
    
    case 'q':
    quitGame = true; // Set the quit flag;
    break;

    // Print error.log contents when debugging flag is on
    case 'x':
    if (debugFlag) {
      ifstream errorFile("error.log");
      if (errorFile) {
        string line;
        while (getline(errorFile, line)) {
          cout << line << endl;
        }
      } else {
        pushError("Error opening error.log for reading.");
      }
    } else {
      pushd("Invalid command.");
      break;
    }
    
    default:
    pushd("Invalid command.");
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
=======
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
  // pushd("Spawn: " + to_string(map.spawn[0]) + ", " + to_string(map.spawn[1]));
  // pushd("Current position: " + to_string(player.x) + ", " + to_string(player.y));
>>>>>>> origin/dev
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

<<<<<<< HEAD
int main() {
  Player player(0, 0); // Initialize player
  Map map; // Initialize map
=======
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
>>>>>>> origin/dev
  
  setup(player, map); // Set up the game with player and map
  
  while (!quitGame) {
<<<<<<< HEAD
    gameLoop(player, map); // Run the game loop
=======
    if (!gamePaused) gameLoop(player, map); // Run the game loop
    // else (to be added)
>>>>>>> origin/dev
  }
  
  clear();
  pushd("Bye, see ya' later... or not. Preferably not.");
  printd();
  
  return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> origin/dev
