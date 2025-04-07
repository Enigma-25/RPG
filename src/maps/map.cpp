#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  // Check if argument is passed
  if (argc < 2) {
    cerr << "Error: No argument provided." << endl;
    return 1;
  }
  
  string arg = argv[1];
  
  if (arg == "--map" || arg == "-m") { // Convert plain text map to special characters
    // Read the map file and add each counterpart to a string
    ifstream mapFile("map.txt");
    if (!mapFile) {
      cerr << "Error opening map.txt" << endl;
      return 1;
    }
    
    string line;
    string mapData;
    
    while (getline(mapFile, line)) {
      for (char c : line) {
        switch (c) {
          case ' ': mapData += "　"; break;
          case 'H': mapData += "Ｈ"; break;
          case '[': mapData += "［"; break;
          case ']': mapData += "］"; break;
          case '#': mapData += "＃"; break;
          case '=': mapData += "＝"; break;
          case '|': mapData += "｜"; break;
          case '-': mapData += "－"; break;
          case 'O': mapData += "Ｏ"; break;
          default: mapData += c; break;  // Keep other characters unchanged
        }
      }
      mapData += "\n"; // Add a newline after each line
    }
    
    mapFile.close();
    
    // Open file for writing new changes
    ofstream outFile("newMap.txt");
    if (!outFile) {
      cerr << "Error opening newMap.txt" << endl;
      return 1;
    }
    
    outFile << mapData; // Write the modified map data to the new file
    outFile.close();
    
    cout << mapData; // Print the modified map data
  }
  else if (arg == "--cmap" || arg == "-c") { // Convert converted map to numeric mapData
    ifstream mapFile("map.txt");  // Use wifstream for wide characters
    if (!mapFile) {
      cerr << "Error opening mao.txt" << endl;
      return 1;
    }

    string line;
    string mapData;

    while (getline(mapFile, line)) {
      for (char c : line) {  // Treat each character as wide character
        switch (c) {
          case ' ': mapData += "0"; break;  // Full-width space
          case 'H': mapData += "1"; break;  // Full-width H
          case '#': mapData += "2"; break;  // Full-width #
          case '|': mapData += "3"; break;  // Full-width |
          case '-': mapData += "4"; break;  // Full-width -
          case '=': mapData += "5"; break;  // Full-width =
          case '[': mapData += "6"; break;  // Full-width [
          case ']': mapData += "7"; break;  // Full-width ]
          default: mapData += c; break;  // Keep other characters unchanged
        }
      }
      mapData += ' '; // Newlines turn to spaces
    }

    mapFile.close();

    if (mapData.empty()) {
      cerr << "Error: No data read from map.txt (mapData is empty for some fckg reason)" << endl;
      return 1;
    }

    // Open file for writing new changes
    ofstream outFile("map.cmap");  // Use wofstream for wide characters
    if (!outFile) {
      cerr << "Error opening map.cmap" << endl;
      return 1;
    }

    // Write the header information
    outFile << "[META]\n";
    outFile << "NAME=\"Map\"\n";
    outFile << "VERSION=\"1.0\"\n";
    outFile << "CREATOR=\"\"\n";
    outFile << "DESCRIPTION=\"Generated with Enigma's mapConverter.\"\n\n";
    outFile << "[MAP]\n";
   
    outFile << mapData; // Write the modified map data to the new file

    outFile << "\n\n# Remember to uncomment the headers before trying to use the map.\n";
    outFile << "\n#[SPECIAL]\n\n";
    outFile << "#[LANG]\n\n";
    outFile << "[EOF]\n"; // End of file marker

    outFile.close();

    cout << "Data written to map.cmap." << endl; // Print the modified map data
  }
  else {
    cerr << "Error: Invalid argument. Use -map (or -m) or -cmap (or -c)." << endl;
    return 1;
  }
  
  return 0;
}
