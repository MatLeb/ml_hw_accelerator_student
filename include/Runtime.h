/**************************************************************************
 * Project     : ML HW Accelerator
 * File        : Runtime.h
 * Description :
 *
 * ------------------------------------------------------------------------
 * Creation    : Mon Sep 25 2023
 * Author      : Mathieu Lebon (ML)
 **************************************************************************/

#ifndef RUNTIME_H
#define RUNTIME_H

#ifndef __SYNTHESIS__
#include <iostream>
#include <chrono>
using namespace std::chrono;

class Runtime
{
public:
  typedef std::chrono::high_resolution_clock::time_point t_time_point;

private:
  t_time_point m_start;
  t_time_point m_stop;

public:
  Runtime() {}

  void start() { m_start = high_resolution_clock::now(); }

  void stop() { m_stop = high_resolution_clock::now(); }

  double getDurationUs()
  {
    return duration_cast<microseconds>(m_stop - m_start).count();
  }
  double getDurationMs()
  {
    return duration_cast<milliseconds>(m_stop - m_start).count();
  }
  double getDurationS()
  {
    return duration_cast<seconds>(m_stop - m_start).count();
  }
  double getDurationM()
  {
    return duration_cast<minutes>(m_stop - m_start).count();
  }

  void printDuration(const char* name)
  {
    std::stringstream ss;
    double t0 = getDurationM();
    double t1 = getDurationS();
    double t2 = getDurationMs();
    double t3 = getDurationUs();

    ss << "[DURATION] (" << name << ") ";
    while (ss.str().length() < 30)
      ss << " ";
    if (t0 > 0)
      ss << t0 << " min" << std::endl;
    else if (t1 > 0)
      ss << t1 << " s" << std::endl;
    else if (t2 > 0)
      ss << t2 << " ms" << std::endl;
    else if (t3 > 0)
      ss << t3 << " us" << std::endl;
    std::cout << ss.str();
  }

};

#else

class Runtime
{

public:
  Runtime() {}

  void start() { }

  void stop() { }

  double getDurationUs()
  {
    return 0;
  }
  double getDurationMs()
  {
    return 0;
  }
  double getDurationS()
  {
    return 0;
  }

  void printDuration(const char* name)
  {
  }

};

#endif
#endif
