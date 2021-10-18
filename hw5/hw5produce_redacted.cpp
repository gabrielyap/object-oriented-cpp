
// g++ -std=c++14 hw5part1.cpp -ljsoncpp
//                Person.cpp Core.cpp MyTime.cpp Post.cpp Reaction.cpp
//                Link.cpp Action.cpp Comment.cpp

#define _ECS36B_DEBUG_

#include "Core.h"
#include "Link.h"
#include "Post.h"
#include "JvTime.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) return -1;

  Json::Value * dumpjv_ptr;

  FILE *jf = fopen(argv[1], "r");
  if (jf == NULL) return -1;

  int i, j;
  long lSize;
  size_t lresult;

  // obtain file size:
  fseek(jf, 0 , SEEK_END);
  lSize = ftell(jf);
  rewind(jf);

  // allocate memory to contain the whole file:
  char *jf_ptr = (char *) malloc(sizeof(char)*lSize);
  // copy the file into the buffer:
  lresult = fread(jf_ptr, 1, lSize, jf);    
  if (lresult != lSize)
    {
      fputs("Reading error", stderr);
      exit (-3);
    }

  Json::Value myv_message;
  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (jf_ptr, jf_ptr + lSize, &myv_message, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  Post my_post { (Person *) NULL, (Message *) NULL };
  bzero(&my_post, sizeof(my_post));

  // "actions"
  vector<Action *> vec_actions;
  if ((myv_message["actions"]["count"]).asInt() > 0)
  {
      for (i = 0; i < (myv_message["actions"]["count"]).asInt(); i++)
	{
	  ...
	}
      my_post.actions = &vec_actions;
  }

  // "comments"
  vector<Comment *> vec_comments;
  vector<Reaction *> * vec_c_reactions_ptr;
  vector<Tag      *> * vec_tag_ptr;
  if ((myv_message["comments"]["count"]).asInt() > 0)
    {
      for (i = 0; i < (myv_message["comments"]["count"]).asInt(); i++)
	{
	  ...

	  // vec_c_reactions_ptr = new vecter<Reaction *> (); // heap, return mAddr of 1st byte
	  // ==> vec_c_reactions_ptr = new vector<Reaction *>();
	  // adding the reactions part
	  for (j = 0; j < (l_jv["reactions"]["count"]).asInt(); j++)
	    {
	      ...
	      // (*vec_c_reactions_ptr).push_back(react_cr_ptr);
	      // (*((void *) 0))).push_back(react_cr_ptr);
	    }
	  comment_ptr->reactions = vec_c_reactions_ptr;

	  // adding the tags part
	  for (j = 0; j < (l_jv["tags"]["count"]).asInt(); j++)
	    {
	      ....
	    }
	  comment_ptr->tags = vec_tag_ptr;

	  // done with one comment, now push back into the comments vector
	  vec_comments.push_back(comment_ptr);
	}
      my_post.comments = &vec_comments;
    }

  // "links"
  vector<Link *> vec_links;
  if ((myv_message["links"]["count"]).asInt() > 0)
    {
      for (i = 0; i < (myv_message["links"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv_message["links"]["data"][i];
	  Link * link_ptr = new Link((l_jv["url"]).asString(),
				     (l_jv["class_id"]).asString(), 
				     (l_jv["object_id"]).asString());
	  vec_links.push_back(link_ptr);
	}
      my_post.links = &vec_links;
    }

  // "message"
  if ((myv_message["message"]).isNull() != true)
    {
      Message *msg_ptr = new Message(myv_message["message"].asString());
      my_post.msg = msg_ptr;
    }

  // "reactions"
  vector<Reaction *> vec_reactions;
  if ((myv_message["reactions"]["count"]).asInt() > 0)
    {
      for (i = 0; i < (myv_message["reactions"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv_message["reactions"]["data"][i];
	  Person *react_p_ptr = new Person((l_jv["avatar_name"]).asString(),
					   (l_jv["vsID"]).asString()); 
	  JvTime *react_cr_time_ptr =
	    new JvTime(((l_jv["created_time"]).asString()).c_str());
	  Reaction * react_ptr = new Reaction(l_jv["type"].asString(),
					      react_p_ptr, react_cr_time_ptr);
	  vec_reactions.push_back(react_ptr);
	}
      my_post.reactions = &vec_reactions;
    }

  // "id"
  char idstr[1024];
  bzero(idstr, 1024);
  sprintf(idstr, "%s", ((myv_message["id"]).asString()).c_str());
  if (idstr[0] != '\0')
    {
      char c_prof_buf[256];
      char c_post_buf[256];
      bzero(c_prof_buf, 256);
      bzero(c_post_buf, 256);
      sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);
      std::string profile_id = { c_prof_buf };
      std::string post_id = { c_post_buf };
      my_post.profile_id = profile_id;
      my_post.post_id = post_id;
    }
  else
    {
      std::cerr << "No Post ID presented" << std::endl;
    }

  // "from"
  Person *author_ptr;
  if ((myv_message["from"]).isNull() != true)
    {
      author_ptr = new Person((myv_message["from"]["avatar_name"]).asString(),
			      (myv_message["from"]["vsID"]).asString()); 
      my_post.author = author_ptr;
    }

  // "to"
  vector<Person *> vec_to;
  if ((myv_message["to"]["count"]).asInt() > 0)
    {
      for (i = 0; i < (myv_message["to"]["count"]).asInt(); i++)
	{
	  Person * to_ptr = new Person((myv_message["to"]["data"][i]["avatar_name"]).asString(),
				       (myv_message["to"]["data"][i]["vsID"]).asString());
	  vec_to.push_back(to_ptr);
	}
      my_post.receivers = &vec_to;
    }

  // "created_time"
  if ((myv_message["created_time"]).isNull() != true)
    {
      my_post.created = new JvTime(((myv_message["created_time"]).asString()).c_str());
    }

  // "updated_time"
  if ((myv_message["updated_time"]).isNull() != true)
    {
      my_post.updated = new JvTime(((myv_message["updated_time"]).asString()).c_str());
    }

  // "is_published"
  my_post.is_published = (myv_message["is_published"]).asBool();

  // now let us print the JSON from C++ objects we just built.
  std::cout << (*(my_post.dumpJ())).toStyledString() << std::endl;

  // process the second json (argc, argv)
  FILE *jf2 = fopen(argv[2], "r");
  if (jf2 == NULL) return -1;

  int i, j;
  long lSize;
  size_t lresult;

  // obtain file size:
  fseek(jf, 0 , SEEK_END);
  lSize = ftell(jf);
  rewind(jf);

  // allocate memory to contain the whole file:
  char *jf2_ptr = (char *) malloc(sizeof(char)*lSize);
  // copy the file into the buffer:
  lresult = fread(jf_ptr, 1, lSize, jf);    
  if (lresult != lSize)
    {
      fputs("Reading error", stderr);
      exit (-3);
    }

  // jf2_ptr ==> second json
  // parse JSON

  Json::Value myv_message2; // this is the guy
  Json::CharReaderBuilder builder2;
  Json::CharReader* reader2 = builder2.newCharReader();
  std::string errors2;
  bool parsingSuccessful2 = reader2->parse
    (jf2_ptr, jf2_ptr + lSize2, &myv_message2, &errors2);
  delete reader2;

  if (!parsingSuccessful2) {
    std::cout << "Failed to parse the content JSON, errors:" << std::endl;
    std::cout << errors2 << std::endl;
  }

  // parsed the second JSON ==> myv_message2
  // definitely NOT want to do the following --
  // Nonono => Post my_post { (Person *) NULL, (Message *) NULL };
  // even worst ==> bzero(&my_post, sizeof(my_post));

  // compare whether these two JSONs belong to the same post

  // "id" check
  char idstr2[1024];
  bzero(idstr2, 1024);
  sprintf(idstr2, "%s", ((myv_message2["id"]).asString()).c_str());
  if (idstr2[0] != '\0')
    {
      char c_prof_buf2[256];
      char c_post_buf2[256];
      bzero(c_prof_buf2, 256);
      bzero(c_post_buf2, 256);
      sscanf(idstr, "%[^_]_%s", c_prof_buf2, c_post_buf2);
      std::string profile_id2 = { c_prof_buf2 };
      std::string post_id2 = { c_post_buf2 };

      if((profile_id2 != my_post.profile_id) ||
	 (post_id2 != my_post.post_id))
	{
	  std::cout << "they are not the same post.\n";
	  exit(-1);
	}
    }
  else
    {
      std::cerr << "No Post ID presented" << std::endl;
      exit(-1);
    }

  // now I can do the merge
  // ...

  // "reactions"
  // this is the key... just use the reactions pointer from the first/only C++ Post object
  std::vector<Reaction *> * vec_reactions2_ptr = my_post.reactions;
  if ((myv_message2["reactions"]["count"]).asInt() > 0)
    {
      for (i = 0; i < (myv_message2["reactions"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv2 = myv_message2["reactions"]["data"][i];
	  Person *react_p2_ptr = new Person((l_jv2["avatar_name"]).asString(),
					   (l_jv2["vsID"]).asString()); 
	  JvTime *react_cr_time2_ptr =
	    new JvTime(((l_jv2["created_time"]).asString()).c_str());
	  Reaction * react2_ptr = new Reaction(l_jv2["type"].asString(),
					      react_p2_ptr, react_cr_time2_ptr);
	  vec_reactions2_ptr.push_back(react2_ptr);
	}
      // you do not need this one ==> my_post.reactions = &vec_reactions;
    }

  //...

  // now let us print the JSON from C++ objects we just built.
  std::cout << (*(my_post.dumpJ())).toStyledString() << std::endl;

  return 0;
}