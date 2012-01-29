CLICPP
----------------------------
This is a helper class for easily collecting and storing settings for your C++ command line application.

The CLICPP class accepts parameters in 3 different ways.

User Input
=============================
With this method, you can allow your application to ask the user for the parameters for your application within the terminal.

Cached User Input
=============================
This method allows you to cache previous inputs from the user so that when they run the application again, they do not have to re-enter previous settings.

Command Line Arguments
=============================
You can also pass arguments directly into this class so that you can run your application using the following syntax.

```
myapplication -first "Travis" -middle "Michael" -last "Tidwell"
```

Example
=============================
The following is an example of how you can use this library in your C++ application.

```cpp
#include <stdio.h>
#include <iostream.h>
#include <cstdlib>
#include "clicpp.h";

// Using the std namespace.
using namespace std;

int main(int argc, char** argv) {

  // Initialize the clicpp variable.
  CLICPP cli(argc, argv);

  // Ask for first and last name and cache them.
  string first = cli.get("first", "What is your first name?", true);
  string last = cli.get("last", "What is your last name?", true);

  // Ask for a password, don't cache, and don't show in the terminal.
  string pass = cli.get("pass", "What is your password?", false, true);

  // Ask for something and don't cache it.
  string param = cli.get("param", "Type something... anything...");

  cout << "Your first name: " << first.c_str() << endl;
  cout << "Your last name: " << last.c_str() << endl;
  cout << "You typed: " << param.c_str() << endl;
  return 0;
}
```
