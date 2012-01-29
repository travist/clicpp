#include <stdio.h>
#include <iostream.h>
#include <cstdlib>
#include "clicpp.h";

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// The length of the line for the config file.
#define CLICPP_LINE_LENGTH 512

// Use the namespace std.
using namespace std;

/**
 * Constructor
 */
CLICPP::CLICPP(int argc, char** argv) {

  // Set the cached configuration.
  setCachedConfig();

  // Iterate through the arguments.
  char * arg;
  string key;
  for (int i=1; i<argc; i++) {
    arg = argv[i];
    if (arg[0] == '-') {
      key = &arg[1];
    }
    else if (key.length() > 0) {

      // Add the setting to the config array.
      tCLICPPSetting setting;
      setting.cache = false;
      setting.value = trim(arg);
      config[trim(key)] = setting;
    }
  }
};

/**
 * Constructor
 */
CLICPP::CLICPP() {

  // Set the cached configuration.
  setCachedConfig();
}

/**
 * Destructor
 */
CLICPP::~CLICPP() {
}

/**
 * See header file for description.
 */
void CLICPP::cache(string name, string value) {
  // Trim both the name and value.
  name = trim(name);
  value = trim(value);

  // Get the config file.
  FILE * pFile = fopen("config", "w+");
  if (pFile != NULL) {
    string line;
    for (tConfigIt i = config.begin(); i != config.end(); i++) {
      if (i->second.cache) {
        line = i->first + string("=") + i->second.value + string("\n");
        fputs(line.c_str(), pFile);
      }
    }
    fclose(pFile);
  }
}

/**
 * See header file for description.
 */
void CLICPP::set(string name, string value, bool setCache) {
  tCLICPPSetting setting;
  setting.cache = setCache;
  setting.value = trim(value);
  config[trim(name)] = setting;
  if (setCache) {
    cache(name, value);
  }
}

/**
 * See header file for description.
 */
string CLICPP::get(string name, string prompt, bool setCache, bool hidden) {

  // If configuration isn't valid.
  if (!configValid(name)) {

    // Prompt the user for input...
    string value;
    cout << prompt.c_str() << ": ";
    setEcho(!hidden);
    getline(cin, value);
    if (hidden) {
      cout << "\n";
    }
    setEcho(true);
    set(name, value, setCache);
  }

  // Return the configuration.
  return config[name].value;
}

/**
 * See header file for description.
 */
void CLICPP::setCachedConfig() {
  string line;
  tCLICPPSetting setting;
  unsigned int delimeter;
  char buffer[CLICPP_LINE_LENGTH];
  FILE * pFile = fopen("config", "r+");
  if (pFile != NULL) {
    while (fgets(buffer, CLICPP_LINE_LENGTH, pFile) != NULL) {
      line = buffer;
      delimeter = line.find("=");
      setting.cache = true;
      setting.value = trim(line.substr(delimeter+1));
      config[trim(line.substr(0, delimeter))] = setting;
    }
    fclose (pFile);
  }
}

/**
 * See header file for description.
 */
bool CLICPP::configValid(std::string name) {
  // Locate the existing config.
  tConfigIt pair = config.find(name);

  // If this pair was found...
  if (pair!=config.end()) {

    // Return that the value is empty.
    return !pair->second.value.empty();
  }
  else {

    // The pair was not found.
    return false;
  }
}

/**
 * See header file for description.
 */
string CLICPP::trim(string str) {
  int i,j,start,end;
  for(i=0,j=0; str[i]!=0; i++) {
    j = ((str[i]<=32)? j+1 : 0);
  }
  end=i-j;
  str = str.substr(0,end);
  return str;
}

/**
 * See header file for description.
 */
void CLICPP::setEcho(bool enable) {
#ifdef WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;
  GetConsoleMode(hStdin, &mode);
  if (!enable) {
    mode &= ~ENABLE_ECHO_INPUT;
  }
  else {
    mode |= ENABLE_ECHO_INPUT;
  }
  SetConsoleMode(hStdin, mode );
#else
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  if (!enable) {
    tty.c_lflag &= ~ECHO;
  }
  else {
    tty.c_lflag |= ECHO;
  }
  (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}