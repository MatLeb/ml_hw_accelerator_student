/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : BaseJson.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 11 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef BASEJSON_H
#define BASEJSON_H

#include <Buffer3D.h>
#include <fstream>
#include <iostream>
#include <list>
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

class BaseJson
{
public:
  // ---------------------------------------------------------------
  // Print json file
  // ---------------------------------------------------------------

  void printJsonFile(const char* filename)
  {
#ifndef __SYNTHESIS__
    std::ifstream jsonFile(filename);
    json parser;
    jsonFile >> parser;
    std::cout << parser.dump(4) << std::endl;
#endif
  }

  void printJsonFile(std::string filename) { printJsonFile(filename.c_str()); }

  // ---------------------------------------------------------------
  // Load data from json file
  // ---------------------------------------------------------------

  template<typename t_list>
  void loadJson(const char* filename, t_list& data)
  {
#ifndef __SYNTHESIS__
    std::cout << "Loading data from " << filename << std::endl;

    std::ifstream jsonFile(filename);
    json parser;
    jsonFile >> parser;
    data = parser.get<t_list>();
#endif
  }

  virtual void loadJson(const char* filename) = 0;

  void loadJson(std::string filename) { loadJson(filename.c_str()); }
};

#endif // BASEJSON_H