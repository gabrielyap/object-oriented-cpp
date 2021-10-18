#include "Post.h"

Post::Post(Person* arg_author, Message* arg_msg)
{
    this->author = arg_author;
    this->msg = arg_msg;
}

Json::Value *Post::dumpJ()
{
    int i;

    Json::Value *result_ptr = new Json::Value();

    // adding id
    (*result_ptr)["id"] = (this->profile_id + "_" + this->post_id);

    // add from
    if (this->author != NULL)
    {
      (*result_ptr)["from"] = (*(this->author)->dumpJ());
    }

    // adding to
    Json::Value json_c_receivers;
    Json::Value json_c_receivers_array;

    if ((this->receivers)->size() > 0)
    {
      for (i = 0; i < (this->receivers)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->receivers))[i])->dumpJ();
            json_c_receivers[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_receivers_array["data"] = json_c_receivers;
      json_c_receivers_array["count"] = ((int) (*(this->receivers)).size());
      (*result_ptr)["to"] = json_c_receivers_array;
    }

    // adding links
    Json::Value json_c_links;
    Json::Value json_c_links_array;

    if ((this->links)->size() > 0)
    {
      for (i = 0; i < (this->links)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->links))[i])->dumpJ();
            json_c_links[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_links_array["data"] = json_c_links;
      json_c_links_array["count"] = ((int) (*(this->links)).size());
      (*result_ptr)["links"] = json_c_links_array;
    }

    // adding tags
    Json::Value json_c_tags;
    Json::Value json_c_tags_array;

    if ((this->tags)->size() > 0)
    {
      for (i = 0; i < (this->tags)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->tags))[i])->dumpJ();
            json_c_tags[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_tags_array["data"] = json_c_tags;
      json_c_tags_array["count"] = ((int) (*(this->tags)).size());
      (*result_ptr)["tags"] = json_c_tags_array;
    }

    // adding actions
    Json::Value json_c_actions;
    Json::Value json_c_actions_array;

    if ((this->actions)->size() > 0)
    {
      for (i = 0; i < (this->actions)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->actions))[i])->dumpJ();
            json_c_actions[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_actions_array["data"] = json_c_actions;
      json_c_actions_array["count"] = ((int) (*(this->actions)).size());
      (*result_ptr)["actions"] = json_c_actions_array;
    }

    // adding created_time
    if (this->created != NULL)
    {
      (*result_ptr)["created_time"] = *((this->created)->getTimeString());
    }

    // adding updated_time
    if (this->updated != NULL)
    {
      (*result_ptr)["updated_time"] = *((this->updated)->getTimeString());
    }

    // adding the message part
    if (this->msg != NULL)
    {
      (*result_ptr)["message"] = (this->msg)->content;
    }

    // adding reactions
    Json::Value json_c_reactions;
    Json::Value json_c_reactions_array;

    if ((this->reactions)->size() > 0)
    {
      for (i = 0; i < (this->reactions)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->reactions))[i])->dumpJ();
            json_c_reactions[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_reactions_array["data"] = json_c_reactions;
      json_c_reactions_array["count"] = ((int) (*(this->reactions)).size());
      (*result_ptr)["reactions"] = json_c_reactions_array;
    }

    // adding comments
    Json::Value json_c_comments;
    Json::Value json_c_comments_array;

    if ((this->comments)->size() > 0)
    {
      for (i = 0; i < (this->comments)->size(); i++)
	    {
            Json::Value * dumpjv_ptr = ((*(this->comments))[i])->dumpJ();
            json_c_comments[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
	    }
      json_c_comments_array["data"] = json_c_comments;
      json_c_comments_array["count"] = ((int) (*(this->comments)).size());
      (*result_ptr)["comments"] = json_c_comments_array;
    }

    // adding is_published
    (*result_ptr)["is_published"] = this->is_published;

  #ifdef _ECS36B_DEBUG_
    std::cout << result_ptr->toStyledString() << std::endl;
  #endif /* _ECS36B_DEBUG_ */
    return result_ptr;
}
