
// JSON_Post.cpp
// #define _ECS36B_DEBUG_

#include "Post.h"

std::map<std::string, OKey *> All_Keys;

std::vector<Post *> *
getPostbyKey
(std::string key)
{
  if (All_Keys.find(key) == All_Keys.end())
    return NULL;
    OKey *okey_ptr = All_Keys[key];
  return okey_ptr->posts;
}

OKey *
getOKey
(std::string key)
{
  if(All_Keys.find(key) != All_Keys.end())
  {
    return All_Keys[key];
  }
  Okey *new_okey_ptr = new Okey(key);
  new_okey_ptr->posts = new std::vector<Post *>();
  All_Keys[key] = new_okey_ptr;
  return new_okey_ptr;
}

std::string
Json_2_PostID
(Json::Value myv)
{
  return ((myv["id"]).asString());
}

Post *
Json_2_Post
(Json::Value myv)
{
  int i, j;

  Post * my_post_ptr = new Post((Person *) NULL, (Message *) NULL);
  bzero(my_post_ptr, sizeof(class Post));

  char idstr[1024];

  // "actions"
if (((myv["actions"]).isNull() != true) &&
    ((myv["actions"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->actions == NULL)
        my_post_ptr->actions = new vector<OKey *>();

      for (i = 0; i < (myv["actions"]["count"]).asInt(); i++)
      {
          Json::Value l_jv = myv["actions"]["data"][i];
          if (l_jv.isNull() != true)
          {
            OKey * okey_ptr = getOKey(l_jv.asString());
            //add Keyword object
            (*(okey_ptr->posts)).push_back(my_post_ptr);
            (*(my_post_ptr->actions)).push_back(okey_ptr);
          }
      }
    }
  // "comments"
...
  // "keys"
if (((myv["keys"]).isNull() != true) &&
    ((myv["keys"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->keys == NULL)
        my_post_ptr->keys = new vector<OKey *>();

      for (i = 0; i < (myv["keys"]["count"]).asInt(); i++)
      {
          Json::Value l_jv = myv["keys"]["data"][i];
          if (l_jv.isNull() != true)
          {
            OKey * okey_ptr = getOKey(l_jv.asString());
            //add Keyword object
            (*(okey_ptr->posts)).push_back(my_post_ptr);
            (*(my_post_ptr->keys)).push_back(okey_ptr);
          }
      }
    }
  // "links"
...
  // "message"
...

  // "reactions"
...
  // "id"
    ...

  // "from"
...

  // "to"
...
  // "created_time"
...

  // "updated_time"
...
  // "is_published"
...
  return my_post_ptr;
}

int
Json_Post_Merging
(Json::Value myv, Post *my_post_ptr)
{
  int i, j;

  char idstr[1024];
  bzero(idstr, 1024);

  // compare ID first
  // "id" (Let us check first if they share the same ID)
  sprintf(idstr, "%s", ((myv["id"]).asString()).c_str());

  if (idstr[0] != '\0')
    {
      char c_prof_buf[256];
      char c_post_buf[256];
      bzero(c_prof_buf, 256);
      bzero(c_post_buf, 256);
      sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);
      std::string profile_id = { c_prof_buf };
      std::string post_id = { c_post_buf };
      if ((my_post_ptr->profile_id != profile_id) ||
	  (my_post_ptr->post_id    != post_id))
	{	  
	  std::cerr << "Post IDs mismatched!!" << std::endl;
	  return -1;
	}
    }
  else
    {
      std::cerr << "No Post ID presented for the second JSON" << std::endl;
      return -2;
    }

  // now, they matched, let us proceed with the merge action

  // "actions"
...
  // "comments"
...
  // "links"
...
  // "message"
...
  // "reactions"
...
  // "id"
  // already done

  // "from"
...
  // "to"
...
  // "created_time"
...
  // "updated_time"
...
  // "is_published"
...

  return 0;
}
