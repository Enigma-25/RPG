#include "main.hpp"

void Map::drawMap(const Player& player) {
  clear(); // Clear the console before drawing the map
  for (int row = 0; row < mapData.size(); ++row) {
    for (int col = 0; col < mapData[row].size(); ++col) {
      if (row == player.y && col == player.x) {
        cout << "Ｏ"; // Draw player
      }
      switch (mapData[row][col]) {
      case EMPTY: cout << "　"; break; // Space
      case WALL: cout << "Ｈ"; break; // Wall
      case CHAIR: cout << "＃"; break; // Chair
      case VERTICAL_DOOR: cout << "｜"; break; // Vertical Door
      case HORIZONTAL_DOOR: cout << "－"; break; // Horizontal Door
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
  spawn[0] = 0; // Set spawn X position
  spawn[1] = 0;  // Set spawn Y position
  
  ifstream mapFile(mapDirectory + "map.cmap");
  if (!mapFile.is_open()) {
    cerr << "Failed to open map file:" << mapDirectory << "map.cmap\n"; 
    return;
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
        vector<Tile> rowData;
        for (char c : row) {
          if (c == 'a') {
            // Set spawn position to position of 'a'
            spawn[0] = rowData.size(); // X position
            spawn[1] = mapData.size(); // Y position
          }

          if (c >= '0' && c <= '9') {
            // Convert numeric characters to enum values
            rowData.push_back(static_cast<Tile>(c - '0'));
          }
        }
      mapData.push_back(rowData);
      }
    }

    if (line == "[SPECIAL]") {
      // Coming soon
    }

    if (line == "[LANG]") {
      // Coming soon
    }

    if (line == "[EOF]") {
      break; // Stop reading when we reach the end
    }

    if (line.empty() || (line[0] == '/' && line[1] == '/')) {
      continue; // Skip empty lines or lines that start withh "//"
    }
  }
  mapFile.close(); // Close the file
}