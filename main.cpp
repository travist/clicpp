/*
 * File:   main.cpp
 * Author: travistidwell
 *
 * Created on January 29, 2012, 1:35 PM
 */
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
  return 1;
}

