#include "main.hpp"

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