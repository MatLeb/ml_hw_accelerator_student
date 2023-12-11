/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : StimRefPath.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 11 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef STIM_REF_PATH_H
#define STIM_REF_PATH_H

#include <string>

#define PATH_STIMREF "../stimref/"

class StimRefPath
{
public:
  static std::string getCoef(const char* filename)
  {
    std::string path(PATH_STIMREF);
    path += "coef/";
    path += filename;
    return path;
  }
  static std::string getCoef(std::string filename)
  {
    return getCoef(filename.c_str());
  }
  static std::string getFmap(const char* filename)
  {
    std::string path(PATH_STIMREF);
    path += "fmap/";
    path += filename;
    return path;
  }
  static std::string getFmap(std::string filename)
  {
    return getFmap(filename.c_str());
  }
};

#endif // STIM_REF_PATH_H