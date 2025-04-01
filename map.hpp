#ifndef MAP_HPP
#define MAP_HPP


class Map {
  public:
    vector<vector<Tile>> mapData; // Map data
    void drawMap(const Player& player); // Draw the map
    void getMapData(); // Fetch map data from file
    int spawn[2]; // Starting position
  };

#endif // MAP_HPP