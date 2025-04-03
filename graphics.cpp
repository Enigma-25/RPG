
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