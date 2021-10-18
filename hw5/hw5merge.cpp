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

  // file size:
  fseek(jf, 0 , SEEK_END);
  lSize = ftell(jf);
  rewind(jf);

  // make memory:
  char *jf_ptr = (char *) malloc(sizeof(char)*lSize);
  // copy the file:
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
    Json::Value l_jv = myv_message["actions"]["data"][i];
    Action *action_ptr = new Action((l_jv["host_url"]).asString(),
       (l_jv["owner_vsID"]).asString(), (l_jv["class_id"]).asString(),
       (l_jv["object_id"]).asString(), (l_jv["name"]).asString());
    vec_actions.push_back(action_ptr);   
	}
      my_post.actions = &vec_actions;
  }


  Comment * comment_ptr;
  vector<Comment *> vec_comments;
  vector<Reaction *> * vec_c_reactions_ptr;
  vector<Tag      *> * vec_tag_ptr = new vector<Tag*> ();
  if ((myv_message["comments"]["count"]).asInt() > 0)
  {
    for (i = 0; i < (myv_message["comments"]["count"]).asInt(); i++)
	  {
	    Json::Value l_jv = myv_message["comments"]["data"][i];

      JvTime *comment_cr_time_ptr = 
      new JvTime(((l_jv["created_time"]).asString()).c_str());

      Person *comment_p_ptr = new Person((l_jv["from"]["avatar_name"]).asString(),
		  (l_jv["from"]["vsID"]).asString()); 

      Message  *message_ptr = new Message(l_jv["message"].asString());

     
      std::string profile_id;
      std::string post_id;
      std::string comment_id;
      
      profile_id = ((l_jv["id"]).asString()).substr(0,39);

      post_id = ((l_jv["id"]).asString()).substr(40,15);

      comment_id = ((l_jv["id"]).asString()).substr(56,15);

	    // reaction
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
      
	    //tags
      vec_tag_ptr = new vector<Tag*> ();
      for (j = 0; j < (l_jv["tags"]["count"]).asInt(); j++)
      {
          Json::Value l_jv_tag = l_jv["tags"]["data"][j];
          Tag * tag_ptr = new Tag();
          tag_ptr->index = (l_jv_tag["index"]).asInt();
          tag_ptr->avatar_name = (l_jv_tag["avatar_name"]).asString();
          tag_ptr->comment = (l_jv_tag["comment"]).asString();
          tag_ptr->vsID = (l_jv_tag["vsID"]).asString();
          vec_tag_ptr->push_back(tag_ptr);
      }

	    comment_ptr = new Comment(profile_id, post_id, comment_id, comment_p_ptr, message_ptr, comment_cr_time_ptr);
      comment_ptr->reactions = vec_c_reactions_ptr;
      comment_ptr->tags = vec_tag_ptr;
	 
	    vec_comments.push_back(comment_ptr);
      
	}
      my_post.comments = &vec_comments;
    }

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

  // message
  if ((myv_message["message"]).isNull() != true)
    {
      Message * msg_ptr = new Message(myv_message["message"].asString());
      my_post.msg = msg_ptr;
    }

  // reactions
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

  // id
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

  // from
  Person *author_ptr;
  if ((myv_message["from"]).isNull() != true)
    {
      author_ptr = new Person((myv_message["from"]["avatar_name"]).asString(),
			      (myv_message["from"]["vsID"]).asString()); 
      my_post.author = author_ptr;
    }

  // to
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

  
  if ((myv_message["created_time"]).isNull() != true)
    {
      my_post.created = new JvTime(((myv_message["created_time"]).asString()).c_str());
    }

 
  if ((myv_message["updated_time"]).isNull() != true)
    {
      my_post.updated = new JvTime(((myv_message["updated_time"]).asString()).c_str());
    }

 
  my_post.is_published = (myv_message["is_published"]).asBool();

  FILE *jf2 = fopen(argv[2], "r");
  if (jf2==NULL) return -1;

  long lSize2;
  size_t lresult2;
  
  fseek(jf2,0,SEEK_END);
  lSize = ftell(jf2);
  rewind(jf2);
  
  char *jf2_ptr = (char*) malloc(sizeof(char)*lSize2);
  lresult2 = fread(jf2_ptr,1,lSize2,jf2);
  if (lresult2 != lSize2)
  {
    fputs("Reading error", stderr);
    exit(-3);
  }
   
  std::cout << (*(my_post.dumpJ())).toStyledString() << std::endl;

  return 0;
}
