
#ifndef _JVTIME_H_
#define _JVTIME_H_

// for Json::value
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

// popular ones
#include <strings.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception> 
#include <time.h>

using namespace std;

class JvTime
{
 private:
 protected:
 public:
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  char tail4[16];

  JvTime(const char *);
  struct std::tm * getStdTM(void);
  std::string * getTimeString(void);
};

#endif /* _JVTIME_H_ */
