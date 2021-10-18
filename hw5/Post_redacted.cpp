#include "Post.h"

Post::Post
(Person * arg_author, Message * arg_msg)
{
  this->author = arg_author;
  this->msg = arg_msg;
}

Json::Value * Post::dumpJ
(void)
{
  int i;

  Json::Value * result_ptr = new Json::Value();
  Json::Value * dumpjv_ptr;

  // "actions"
  if (this->actions != NULL)
    {

    }

  // comments
  if (this->comments != NULL)
    {

    }

  // "links"
  if (this->links != NULL)
    {

    }

  // "message"
  if (this->msg != NULL)
    {

    }

  // "reactions"
  if (this->reactions != NULL)
    {
      Json::Value json_reactions;
      Json::Value json_reactions_array;
      for (i = 0; i < (this->reactions)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->reactions))[i])->dumpJ();
	  json_reactions[i] = (*dumpjv_ptr);
	  delete dumpjv_ptr;
	}
      json_reactions_array["data"] = json_reactions;
      json_reactions_array["count"] = ((int) (*(this->reactions)).size());
      // std::cout << json_reactions_array.toStyledString() << std::endl;
      (*result_ptr)["reactions"] = json_reactions_array;
    }

  // "id"
  (*result_ptr)["id"] = (this->profile_id + "_" + this->post_id);

  // "from"
  if (this->author != NULL)
    {
      dumpjv_ptr = (this->author)->dumpJ();
      (*result_ptr)["from"] = (*dumpjv_ptr);
      delete dumpjv_ptr;
    }

  // "to"
  if (this->receivers != NULL)
    {

    }

  // "created_time"
  if (this->created != NULL)
    {
      (*result_ptr)["created_time"] = *((this->created)->getTimeString());
    }

  // "updated_time"
  if (this->updated != NULL)
    {
      (*result_ptr)["updated_time"] = *((this->updated)->getTimeString());
    }

  // "is_published"
  (*result_ptr)["is_published"] = this->is_published;

#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}