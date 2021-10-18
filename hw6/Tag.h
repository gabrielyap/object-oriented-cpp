
#ifndef _TAG_H_
#define _TAG_H_

// Tag.h
#include "Core.h"

class Tag
{
 private:
 protected:
 public:
  int index;
  std::string avatar_name;
  std::string vsID;
  std::string comment;

  Tag();
  Tag(int index, std::string, std::string);
  Tag(int index, std::string);
  Tag(int index, std::string, std::string, std::string);
  Json::Value * dumpJ();
};

#endif /* _TAG_H_ */
