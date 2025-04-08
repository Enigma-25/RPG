#include "main.hpp"

// Map class method implementations
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
    pushError("Failed to open map: " + mapName + " from " + mapPath); 
    return;
  }
  
  string line, mapDataSection;
  
  while (getline(mapFile, line)) {
    if (line == "[MAP]") { readMapSection(mapFile, line, mapDataSection, spawn); break; }
    
    if (line == "[SPECIAL]") { readSpecialSection(mapFile, line); break; }
    
    if (line.empty() || line[0] == '#') { continue; }
    if (line == "[EOF]") { break; }
  }
  mapFile.close();
}

void Map::readSpecialSection(ifstream& mapFile, string& line) {
  // Handle special ID section
  while (getline(mapFile, line)) {
    if (line.empty() || line[0] == '[') break;
    
    istringstream specialStream(line);
    size_t x, y;
    int id;
    
    if (!(specialStream >> x)) {
      pushError("Error: Invalid x coordinate in special section");
      continue;
    }
    
    if (specialStream.get() != ',') {
      pushError("Error: Expected ',' in special section");
      continue;
    }
    
    if (!(specialStream >> y)) {
      pushError("Error: Invalid y coordinate in special section");
      continue;
    }
    
    if (specialStream.get() != ':') {
      pushError("Error: Expected ':' in special section");
      continue;
    }
    
    if (!(specialStream >> id)) {
      pushError("Error: Invalid Special ID in special section");
      continue;
    }
    
    if (y < mapData.size() && x < mapData[y].size()) {
      mapData[y][x].specialID = id;
    } else {
      pushError("Error: Special ID coordinates out of bounds: (" + 
                to_string(x) + ", " + to_string(y) + ") with ID " + 
                to_string(id) + " because of " + to_string(mapData.size()) + 
                " rows and " + to_string(mapData[y].size()) + " columns.");
    }
  }
}

void Map::readMapSection(ifstream& mapFile, string& line, string& mapDataSection, int spawn[2]) {
  while (getline(mapFile, line)) {
    if (line.empty() || line[0] == '[') break;
    mapDataSection += line + " ";
  }
  
  istringstream mapStream(mapDataSection);
  string row;
  while (mapStream >> row) {
    vector<Tile> rowData;
    
    for (char c : row) {
      Tile tile;
      
      if (c == 'X') {
        spawn[0] = rowData.size();
        spawn[1] = mapData.size();
      }
      
      if (c >= '0' && c <= '9') {
        tile.tileType = static_cast<TileType>(c - '0');
        
        switch (tile.tileType) {
          case TABLE:
          case WALL:          tile.setProperty(solid);        break;
          case CHAIR:
          case VERTICAL_DOOR:
          case HORIZONTAL_DOOR:
          case LEFT_PANEL:
          case RIGHT_PANEL:   tile.setProperty(interactable); break;
          default: break;
        }
      }
      
      tile.specialID = -1;
      rowData.push_back(tile);
    }
    mapData.push_back(rowData);
  }
}
