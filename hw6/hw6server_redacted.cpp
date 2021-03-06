
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>
#include <cstring>

// for JsonRPCCPP
#include <iostream>
#include "hw6server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs36b_hw6
#include "Post.h"

std::map<std::string, Post *> Post_Map;

using namespace jsonrpc;
using namespace std;

class Myhw6Server : public hw6Server
{
public:
  Myhw6Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value update(const std::string& updating_json);
  virtual Json::Value search(const std::string& search_clause);
};

Myhw6Server::Myhw6Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw6Server(connector, type)
{
  std::cout << "Myhw6Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw6Server::update(const std::string& updating_json)
{
  Json::Value result_json;
  char fname_buf[1024];
  FILE * post_f_ptr;

  int rc = 0;

  std::cout << Post_Map.size() << std::endl;

#ifdef _ECS36B_DEBUG_
  std::cout << "update" << " " << updating_json << std::endl;
#endif /* _ECS36B_DEBUG_ */

  Post * post_ptr = NULL;

  Json::CharReaderBuilder builder;
  Json::CharReader* reader;
  std::string errors;
  bool parsingSuccessful;

  Json::Value myv_message;
  reader = builder.newCharReader();
  parsingSuccessful = reader->parse(updating_json.c_str(),
				    updating_json.c_str() + updating_json.size(),
				    &myv_message, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  // set the json_post file name
  bzero(fname_buf, 1024);
  sprintf(fname_buf, "post_%s.json", ((myv_message["id"]).asString()).c_str());

  long lSize;
  size_t lresult;

  if (Post_Map.find((myv_message["id"]).asString()) != Post_Map.end())
    {
      // we need to merge
      rc = 0;
      post_ptr = Post_Map[(myv_message["id"]).asString()];
      rc = Json_Post_Merging(myv_message, post_ptr);
    }
  else
    {
      rc = 0;
      // check if there is a file for this post --
      post_f_ptr = fopen(fname_buf, "r");
      if (post_f_ptr != NULL)
      {
        fseek(post_f_ptr, 0 , SEEK_END);
        lSize = ftell(post_f_ptr);
        rewind(post_f_ptr);
        //allocate memory to contain whole file
        char *pjf_ptr = (char *) malloc(sizeof(char)*lSize);
        //copy result
        lresult = fread(pjf_ptr, 1 , lSize, post_f_ptr);
        if (lresult != lSize)
        {
          fputs("Reading error", stderr);
          exit (-3);
        }

        Json::Value pjf_v;
        reader = builder.newCharReader();
        parsingSuccessful = reader->parse(pjf_ptr, pjf_ptr + lSize, &pjf_v, &errors);
        delete reader;

        if (!parsingSuccessful)
        {
          std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
          std::cout << errors << std::endl;
        }
        post_ptr = Json_2_Post(pjf_v);
        if (post_ptr == NULL) rc = -1;
        else
        {
          Post_Map[(myv_message["id"]).asString()] = post_ptr;
          rc = Json_Post_Merging(myv_message, post_ptr);
        }

        fclose(post_f_ptr);
        
      }
      else
      {
        //create new post
        post_ptr = Json_2_Post(myv_message);
        if (post_ptr == NULL) rc = -1;
        else
        {
            Post_Map[(myv_message["id"]).asString()] = post_ptr;
        }
        
      }

    }

  if (rc < 0)
    {
      std::string strJson;
      strJson += "{\"status\" : \"failed\"}";
      reader = builder.newCharReader();
      parsingSuccessful = reader->parse
    	(strJson.c_str(), strJson.c_str() + strJson.size(), &result_json, &errors);
      delete reader;

      if (!parsingSuccessful) {
	    std::cout << "Failed to parse the JSON, errors:" << std::endl;
	    std::cout << errors << std::endl;
      }
      
      return result_json;
    }

  // write it back
  // std::cout << fname_buf <<  std::endl;
  post_f_ptr = fopen(fname_buf, "w");
  if (post_f_ptr != NULL)
    {
      char post_json_buf[8192]; // limited size
      bzero(post_json_buf, 8192);
      sprintf(post_json_buf, "%s", ((*(post_ptr->dumpJ())).toStyledString()).c_str());
      lSize = strlen(post_json_buf);
      std::cout << fname_buf << " " << lSize <<  std::endl;
      lresult = fwrite(post_json_buf, 1, lSize, post_f_ptr);    
      if (lresult != lSize)
	{
	  fputs("Reading error", stderr);
	  exit (-3);
	}
      fclose(post_f_ptr);
    }

  std::cout << Post_Map.size() << std::endl;
  return (*(post_ptr->dumpJ()));
}

Json::Value
Myhw6Server::search
(const std::string& search_clause)
{
  Json::Value result_json;
  int rc = 0;

#ifdef _ECS36B_DEBUG_
  std::cout << "search" << " " << search_clause << std::endl;
#endif /* _ECS36B_DEBUG_ */
  std::cout << "search" << " " << search_clause << std::endl;

  Json::CharReaderBuilder builder;
  Json::CharReader* reader;
  std::string errors;
  bool parsingSuccessful;

  Json::Value myv_message;
  reader = builder.newCharReader();
  parsingSuccessful = reader->parse(search_clause.c_str(),
				    search_clause.c_str() + search_clause.size(),
				    &myv_message, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  Json::Value json_data;
  if ((myv_message["keyword"]).isNull() == true)
    {
      rc = -1;
    }
  else
    {
      std::vector<Post *> *pv_ptr = getPostbyKey((myv_message["keyword"]).asString());
      if (pv_ptr == NULL)
      {
        rc = -2;
      }
      else
      {
        int i;
        Json::Value *dumpjv_ptr;

        for (i = 0; i < pv_ptr->size(); i++)
        {
          dumpjv_ptr = ((*pv_ptr)[i])->dumpJ();
          json_data[i] = (*dumpjv_ptr);
          delete dumpjv_ptr;
        }
        result_json["data"] = json_data;
        result_json["count"] = ((int) pv_ptr->size());
      }
    }

  // std::cout << "rc = " << " " << rc << std::endl;
  // std::cout << (json_data).toStyledString() << std::endl;

  if (rc < 0)
    {
      std::string strJson;
      strJson += "{\"status\" : \"failed\"}";
      reader = builder.newCharReader();
      parsingSuccessful = reader->parse
	(strJson.c_str(), strJson.c_str() + strJson.size(), &result_json, &errors);
      delete reader;

      if (!parsingSuccessful) {
	std::cout << "Failed to parse the JSON, errors:" << std::endl;
	std::cout << errors << std::endl;
      }
    }

  // std::cout << (result_json).toStyledString() << std::endl;

  return result_json;
}

int
main(void)
{
  HttpServer httpserver(8384);
  Myhw6Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
