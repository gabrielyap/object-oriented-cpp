
#ifndef _POST_H_
#define _POST_H_

// Post.h
#include "Core.h"
#include "Tag.h"
#include "Comment.h"
#include "Reaction.h"
#include "Message.h"
#include "Person.h"
#include "Link.h"
#include "Action.h"
#include "JvTime.h"

class Post
{
 private:
 protected:
 public:
  std::string profile_id;
  std::string post_id;

  Person * author;
  std::vector<Person *> * receivers;

  Message * msg;
  std::vector<Link *> * links;
  std::vector<Action *> * actions;
  std::vector<Reaction *> * reactions;
  std::vector<Comment *> * comments;

  JvTime * created;
  JvTime * updated;
  bool is_published;

  Post(Person* arg_author, Message* arg_msg);
  Json::Value * dumpJ();
};

#endif /* _POST_H_ */
