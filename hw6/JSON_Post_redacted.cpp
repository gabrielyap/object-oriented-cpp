
// JSON_Post_redacted.cpp
// #define _ECS36B_DEBUG_

#include <arpa/inet.h>
#include "Post.h"

int
Json_Post_Common
(Json::Value myv, Post * my_post_ptr)
{
  int i, j;
  

  // under Json_Post_Common, we assume that the ID already matched
  // for both Post and myv

  // "actions"
vector<Action *> vec_actions;
  if ((myv["actions"]["count"]).asInt() > 0)
  {
      for (i = 0; i < (myv["actions"]["count"]).asInt(); i++)
	{
    Json::Value l_jv = myv["actions"]["data"][i];
    Action *action_ptr = new Action((l_jv["host_url"]).asString(),
       (l_jv["owner_vsID"]).asString(), (l_jv["class_id"]).asString(),
       (l_jv["object_id"]).asString(), (l_jv["name"]).asString());
    vec_actions.push_back(action_ptr); 
	}
  
      my_post_ptr->actions = &vec_actions;
      //error below
  }

  // "comments"
Comment * comment_ptr;
  vector<Comment *> vec_comments;
  vector<Reaction *> * vec_c_reactions_ptr;
  vector<Tag      *> * vec_tag_ptr = new vector<Tag*> ();
  if ((myv["comments"]["count"]).asInt() > 0)
  {
    for (i = 0; i < (myv["comments"]["count"]).asInt(); i++)
	  {
	    Json::Value l_jv = myv["comments"]["data"][i];
			
      // set JvTime
      JvTime *comment_cr_time_ptr = 
      new JvTime(((l_jv["created_time"]).asString()).c_str());
			
      // set author
      Person *comment_p_ptr = new Person((l_jv["from"]["avatar_name"]).asString(),
		  (l_jv["from"]["vsID"]).asString()); 
			
      // set message
      Message  *message_ptr = new Message(l_jv["message"].asString());

      // breaking up id parts
      std::string profile_id;
      std::string post_id;
      std::string comment_id;
      
      // set profile, post, and comment ids
      profile_id = ((l_jv["id"]).asString()).substr(0,39);
      post_id = ((l_jv["id"]).asString()).substr(40,15);
      comment_id = ((l_jv["id"]).asString()).substr(56,15);

	    // adding the reactions part
      //error below 
      vec_c_reactions_ptr = new vector<Reaction*> ();
	    for (j = 0; j < (l_jv["reactions"]["count"]).asInt(); j++)
	    {
	    Json::Value l_jv_react = l_jv["reactions"]["data"][j];
	    Person *react_p_ptr = new Person((l_jv_react["avatar_name"]).asString(),
		  (l_jv_react["vsID"]).asString()); 
	    JvTime *react_cr_time_ptr = 
            new JvTime(((l_jv_react["created_time"]).asString()).c_str());
	    Reaction * react_ptr = new Reaction((l_jv_react["type"]).asString(),
	            react_p_ptr, react_cr_time_ptr);
	    vec_c_reactions_ptr->push_back(react_ptr);
	    }
	    // adding the tags part
      //std::cout<<"SPACE1"<<std::endl; //= error below
      if ( ((l_jv["tags"]).isNull() != true) && ((l_jv["tags"]["count"]).asInt() > 0))
      {
        //std::cout<<"SPACE2"<<std::endl; //error comes here
        vec_tag_ptr = new vector<Tag*> ();

      
      for (j = 0; j < (l_jv["tags"]["count"]).asInt(); j++)
      {
          //error above
          Json::Value l_jv_tag = l_jv["tags"]["data"][j];
          if ((l_jv_tag["comment"]).asString() == "")
          {
              Tag * tag_ptr = new Tag((l_jv_tag["index"]).asInt(), (l_jv_tag["avatar_name"]).asString(),
                                      (l_jv_tag["vsID"]).asString());
              vec_tag_ptr->push_back(tag_ptr);
          }
          else if((l_jv_tag["vsID"]).asString() == "")
          {
            Tag *tag_ptr = new Tag((l_jv_tag["index"]).asInt(), (l_jv_tag["comment"]).asString());
            vec_tag_ptr->push_back(tag_ptr);
          }
          else
          {
            Tag *tag_ptr = new Tag((l_jv_tag["index"]).asInt(), (l_jv_tag["avatar_name"]).asString(),
                                      (l_jv_tag["vsID"]).asString(), (l_jv_tag["comment"]).asString());
            vec_tag_ptr->push_back(tag_ptr);
          }
      }
          comment_ptr->tags = vec_tag_ptr;
      }
          else
          {
            comment_ptr->tags = NULL;
          }
          
          
          
          //std::cout<<"SPACE"<<std::endl;
          //tag_ptr->index = (l_jv_tag["index"]).asInt();
          //tag_ptr->avatar_name = (l_jv_tag["avatar_name"]).asString();
          //tag_ptr->comment = (l_jv_tag["comment"]).asString();
          //tag_ptr->vsID = (l_jv_tag["vsID"]).asString();
          //vec_tag_ptr->push_back(tag_ptr);
      comment_ptr = new Comment(profile_id, post_id, comment_id, comment_p_ptr, message_ptr, comment_cr_time_ptr);
      comment_ptr->reactions = vec_c_reactions_ptr;
      comment_ptr->tags = vec_tag_ptr;
	    // done with one comment, now push back into the comments vector
	    vec_comments.push_back(comment_ptr);
      
	}
      my_post_ptr->comments = &vec_comments;
      }
      

	//     comment_ptr = new Comment(profile_id, post_id, comment_id, comment_p_ptr, message_ptr, comment_cr_time_ptr);
  //     comment_ptr->reactions = vec_c_reactions_ptr;
  //     comment_ptr->tags = vec_tag_ptr;
	//     // done with one comment, now push back into the comments vector
	//     vec_comments.push_back(comment_ptr);
      
	// }
  //     my_post_ptr->comments = &vec_comments;
  //   }

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
vector<Link *> vec_links;
    if ((myv["links"]["count"]).asInt() > 0)
  {
      for (i = 0; i < (myv["links"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv["links"]["data"][i];
	  Link * link_ptr = new Link((l_jv["url"]).asString(),
				     (l_jv["class_id"]).asString(), 
				     (l_jv["object_id"]).asString());
	  vec_links.push_back(link_ptr);
 }
      my_post_ptr->links = &vec_links;
    }



  // "message"
 if ((myv["message"]).isNull() != true)
    {
      Message * msg_ptr = new Message(myv["message"].asString());
      my_post_ptr->msg = msg_ptr;
    }

  // "reactions" 
    if (((myv["reactions"]).isNull() != true) &&
	((myv["reactions"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->reactions == NULL)
	my_post_ptr->reactions = new vector<Reaction *>();

      for (i = 0; i < (myv["reactions"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv["reactions"]["data"][i];

	  if (((l_jv["avatar_name"]).isNull() != true) &&
	      ((l_jv["vsID"]).isNull() != true) &&
	      ((l_jv["created_time"]).isNull() != true) &&
	      ((l_jv["type"]).isNull() != true))
	    {

	      Person *react_p_ptr = new Person((l_jv["avatar_name"]).asString(),
					       (l_jv["vsID"]).asString()); 
	      JvTime *react_cr_time_ptr =
		new JvTime(((l_jv["created_time"]).asString()).c_str());
	      Reaction * react_ptr = new Reaction(l_jv["type"].asString(),
						  react_p_ptr, react_cr_time_ptr);

	      (*(my_post_ptr->reactions)).push_back(react_ptr);

	    }
	}
    }

  // "history"
//...

  // "id"
  // already done

  // "from"
  // this could be a from replacement
 //Person *author_ptr;
  if ((myv["from"]).isNull() != true)
    {
      Person *author_ptr = new Person((myv["from"]["avatar_name"]).asString(),
			      (myv["from"]["vsID"]).asString()); 
      my_post_ptr->author = author_ptr;
    }


  // "to"
    if (((myv["to"]).isNull() != true) &&
	((myv["to"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->receivers == NULL)
	my_post_ptr->receivers = new vector<Person *>();

      for (i = 0; i < (myv["to"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv["to"]["data"][i];

	  if (((l_jv["avatar_name"]).isNull() != true) &&
	      ((l_jv["vsID"]).isNull() != true))
	    {
	      Person * to_ptr = new Person((l_jv["avatar_name"]).asString(),
					   (l_jv["vsID"]).asString());

	      (*(my_post_ptr->receivers)).push_back(to_ptr);
	    }
	}
    }

  // "created_time"
  if ((myv["created_time"]).isNull() != true)
    {
      my_post_ptr->created = new JvTime(((myv["created_time"]).asString()).c_str());
    }

  // "updated_time"
  if ((myv["updated_time"]).isNull() != true)
    {
      my_post_ptr->updated = new JvTime(((myv["updated_time"]).asString()).c_str());
    }


  // "is_published"
  my_post_ptr->is_published = (myv["is_published"]).asBool();

  return 0;
}


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
  if (All_Keys.find(key) != All_Keys.end())
    return All_Keys[key];

  OKey *new_okey_ptr = new OKey(key);
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

// here it is

Post *
Json_2_Post
(Json::Value myv)
{
  if (myv.isArray() == true)
    {
      // wrong one
      // {...}
      // [...] NULL
      return NULL;
    }

  Post * my_post_ptr = new Post((Person *) NULL, (Message *) NULL);

  // "id"
  if ((myv["id"]).isNull() != true)
    {
      char idstr[1024];
      bzero(idstr, 1024);
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

	  // put id attributes to the Post object
	  my_post_ptr->profile_id = profile_id;
	  my_post_ptr->post_id = post_id;
	}
      else
	{
	  std::cerr << "No Post ID presented" << std::endl;
	  exit(-1);
	}
    }
  else
    {
      std::cerr << "No Post ID presented" << std::endl;
      exit(-2);
    }

  int rc = Json_Post_Common(myv, my_post_ptr);
  if (rc != 0)
    {
      std::cerr << "Error Json_Post_Common " << rc << std::endl;
      exit(-3);
    }

  return my_post_ptr;
}


int
Json_Post_Merging
(Json::Value myv, Post * my_post_ptr)
{
  char idstr[1024];
  bzero(idstr, 1024);

  if ((myv).isArray() == true) return -3;
  if ((myv["id"]).isNull() == true) return -1;

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
  return Json_Post_Common(myv, my_post_ptr);
}

