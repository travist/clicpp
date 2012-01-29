/*
 * File:   clicpp.h
 * Author: travistidwell
 *
 * Created on January 28, 2012, 9:12 PM
 */

#ifndef CLICPP_H
#define	CLICPP_H

#include <string.h>
#include <map>

/**
 * A structure to keep track of the settings for each config item.
 */
struct tCLICPPSetting {
  bool cache;
  std::string value;
};

// A map of the configuration settings.
typedef std::map<std::string, tCLICPPSetting> tConfig;

// Create a typedef for the configuration iterator.
typedef std::map<std::string, tCLICPPSetting>::const_iterator tConfigIt;

/**
 * This is a helper class to assist with creating command line applications
 * in C++ where you can easily gather settings for your application.
 *
 * See main.cpp for a sample implementation.
 *
 * @param argc
 * @param argv
 */
class CLICPP {

public:
  CLICPP(int argc, char** argv);
  CLICPP();
  ~CLICPP();

  /**
   * Set the output echo to on or off for gathering settings.
   * @param state
   */
  void setEcho(bool state=false);

  /**
   * Cache the name and value of a setting into a "cache" file.
   * @param name
   * @param value
   */
  void cache(std::string name, std::string value);

  /**
   * Set the value of a setting within the config array.
   * @param name
   * @param value
   * @param cache
   */
  void set(std::string name, std::string value, bool cache = false);

  /**
   * Get the value of a config setting.
   *
   * @param name
   * @param prompt
   * @param cache
   * @param hidden
   * @return
   */
  std::string get(std::string name, std::string prompt, bool cache = false, bool hidden = false);

private:

  /**
   * String trim function.
   * Retrieved from http://www.zedwood.com/article/107/cpp-trim-function
   *
   * @param str
   * @return
   */
  std::string trim(std::string str);

  /**
   * Sets the cached configuration.
   */
  void setCachedConfig();

  /**
   * Determines if the configuration is valid.
   * @param
   * @return bool TRUE the config is valid, FALSE otherwise.
   */
  bool configValid(std::string);

  /**
   * The configuration.
   */
  tConfig config;
};

#endif	/* CLICPP_H */

