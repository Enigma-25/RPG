#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to convert plain text map to special characters and save it to a new file (what it would look like in-game)
int plainToMap() {
  ifstream mapFile("map.txt");
  if (!mapFile) {
    cerr << "Error: Couldn't open map.txt" << endl;
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
  
  ofstream outFile("newMap.txt");
  if (!outFile) {
    cerr << "Error: Couldn't open newMap.txt" << endl;
    return 1;
  }
  
  outFile << mapData; // Write the modified map data to the new file
  outFile.close();
  
  cout << "newMap.txt:\n" << mapData << endl; // Print the modified map data
  return 0;
}

// Function to convert plain map to numeric mapData for game processing
int plainToCmap() {
  ifstream mapFile("map.txt");
  if (!mapFile) {
    cerr << "Error opening map.txt" << endl;
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
  return 0;
}

// Function to reverse Cmap numerical data into plain character map
int cmapToPlain() {
  ifstream cmapFile("map.cmap");
  if (!cmapFile) {
    cerr << "Error: Couldn't open map.cmap" << endl;
    return 1;
  }
  
  string line;
  string mapData;
  
  while (getline(cmapFile, line)) {
    if (line == "[MAP]") {
      break; // Skip the meta data part
    }
  }

  while (getline(cmapFile, line)) {
    for (char& c : line) {
      switch (c) {
        case '0': mapData += " ";  break;  // Empty space
        case '1': mapData += "H";  break;  // H
        case '2': mapData += "#";  break;  // #
        case '3': mapData += "|";  break;  // |
        case '4': mapData += "-";  break;  // -
        case '5': mapData += "=";  break;  // =
        case '6': mapData += "[";  break;  // [
        case '7': mapData += "]";  break;  // ]
        case ' ': mapData += '\n'; break;  // Newline
        default:                   break;
      }
    }
    mapData += "\n"; // Add a newline after each line
  }
  
  cmapFile.close();
  
  ofstream outFile("map.txt");
  if (!outFile) {
    cerr << "Error: Couldn't open map.txt" << endl;
    return 1;
  }

  outFile << mapData; // Write the converted plain text map to map.txt
  outFile.close();
  
  cout << "map.txt:\n" << mapData << endl; // Print the plain text map
  return 0;
}

// Function to reverse Cmap numerical data into special character map
int cmapToMap() {
  ifstream cmapFile("map.cmap");
  if (!cmapFile) {
    cerr << "Error: Couldn't open map.cmap" << endl;
    return 1;
  }

  string line;
  string mapData;
  
  while (getline(cmapFile, line)) {
    if (line.substr(0, 5) == "[MAP]") {
      break; // Skip the meta data part
    }
  }

  while (getline(cmapFile, line)) {
    for (char& c : line) {
      switch (c) {
        case '0': mapData += "　"; break;  // Full-width space
        case '1': mapData += "Ｈ"; break;  // Full-width H
        case '2': mapData += "＃"; break;  // Full-width #
        case '3': mapData += "｜"; break;  // Full-width |
        case '4': mapData += "－"; break;  // Full-width -
        case '5': mapData += "＝"; break;  // Full-width =
        case '6': mapData += "［"; break;  // Full-width [
        case '7': mapData += "］"; break;  // Full-width ]
        case ' ': mapData += '\n'; break;  // Newline
        default: mapData += c; break;  // Keep other characters unchanged
      }
    }
    mapData += "\n"; // Add a newline after each line
  }

  cmapFile.close();

  ofstream outFile("newMap.txt");
  if (!outFile) {
    cerr << "Error: Couldn't open newMap.txt" << endl;
    return 1;
  }

  outFile << mapData; // Write the converted special character map to newMap.txt
  outFile.close();

  cout << "newMap.txt:\n" << mapData << endl; // Print the special character map
  return 0;
}

void help() {
  cout  << "Usage: unmap [OPTION] {--reverse | -r}\n\n"
        << "(Enigma(25)'s) Unnamed Map Builder converts between different map formats for (Enigma(25)'s) Unnamed RPG (Engine) or combines correctly converted files to build a .cmap file for (Enigma(25)'s) Unnamed RPG (Engine).\n"
        << "This program is still a work in progress, so some features may not be fully functional.\n\n"
        << "Options:\n"
        << "  --interactive,    -i    Run the program in interactive mode where the process is prompted\n"
        << "  --plain-to-map,   -m    Convert a plain text map to special characters\n"
        << "  --map-to-cmap,    -c    Convert a plain text map to cmap format for game-engine usage\n"
        << "  --reverse         -r    Reverse the given process (only works as a second argument)\n"
        << "  --build ,         -b    Combine multiple converted files to build a .cmap file\n"
        << "  --help,           -h    Show this help message\n"
        << "  --version,        -v    Show version information\n"
        << "  --author,         -a    Show author information\n\n"
        << "Usage Examples:\n"
        << "  Convert a plain text map to special characters (what it would look like in the game):\n"
        << "    unmap --map\n"
        << "    Output file: 'newMap.txt'\n\n"
        << "  Convert a plain text map to cmap a cmap template:\n"
        << "    unmap --cmap\n"
        << "    Output file: 'map.txt'\n\n"
        << "  (Reverse) Map of special characters to plain-text\n"
        << "    unmap --map --reverse\n\n"
        << "Version: 1.0.0\n"
        << "Author: Enigma(25)\n";
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Error: No argument provided." << endl;
    return 1;
  }
  
  string arg = argv[1];
  
  if (arg == "--map" || arg == "-m") {
    plainToMap();
  }
  else if (arg == "--cmap" || arg == "-c") {
    plainToCmap();
  }
  else if (arg == "--reverse" || arg == "-r") {
    if (argc < 3) {
      cerr << "Error: No reverse argument specified." << endl;
      return 1;
    }
    string reverseArg = argv[2];
    if (reverseArg == "--map" || reverseArg == "-m") {
      cmapToMap();
    } else if (reverseArg == "--cmap" || reverseArg == "-c") {
      cmapToPlain();
    } else {
      cerr << "Error: Invalid reverse argument." << endl;
      help();
      return 1;
    }
  }
  else if (arg == "--help" || arg == "-h") {
    help();
  }
  else if (arg == "--version" || arg == "-v") {
    cout << "Version: 1.0.0" << endl;
  }
  else if (arg == "--author" || arg == "-a") {
    cout << "Author: Enigma(25)" << endl;
  }
  else {
    cerr << "Error: Invalid argument." << endl;
    help();
    return 1;
  }

  return 0;
}
