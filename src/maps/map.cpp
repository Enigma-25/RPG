#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to convert plain text map to special characters and save it to a new file (what it would look like in-game)
int plainToMap() {
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

// Function to convert special characters back to plain text
int cmapUnStaging() {
  // Coming soon
}

// Function to convert plain map to numeric mapData for game processing
int plainToCmap() {
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

void help() {
  cout  << "Usage: <command> [[--map | -m] | [--cmap | -c]]\n"
        << "  --map, -m   Convert plain text map to special characters\n"
        << "  --cmap, -c  Convert special characters back to plain text\n"
        << "  --help, -h  Show this help message\n";
}

int main(int argc, char* argv[]) {
  // Check if argument is passed
  if (argc < 2) {
    cerr << "Error: No argument provided." << endl;
    return 1;
  }
  
  string arg = argv[1];
  
  if (arg == "--map" || arg == "-m")          plainToMap();
  else if (arg == "--cmap" || arg == "-c")    plainToCmap();
  else if (arg == "--help" || arg == "-h")    help();
  else if (arg == "--version" || arg == "-v") cout << "Version: 1.0.0 (I don't feel like maintaning versioning)" << endl;
  else if (arg == "--author" || arg == "-a")  cout << "Author: Enigma(25)" << endl;
  else cerr << "Error: Invalid argument." << endl; help(); return 1;
  
  return 0;
}
