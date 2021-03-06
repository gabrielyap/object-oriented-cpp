/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_HW3SERVER_H_
#define JSONRPC_CPP_STUB_HW3SERVER_H_

#include <jsonrpccpp/server.h>

class hw3Server : public jsonrpc::AbstractServer<hw3Server>
{
    public:
        hw3Server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<hw3Server>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("GetDistance", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "action",jsonrpc::JSON_STRING,"arguments",jsonrpc::JSON_STRING,"class_id",jsonrpc::JSON_STRING,"host_url",jsonrpc::JSON_STRING,"object_id",jsonrpc::JSON_STRING,"owner_vsID",jsonrpc::JSON_STRING, NULL), &hw3Server::GetDistanceI);
            this->bindAndAddMethod(jsonrpc::Procedure("Conflict_of_Interest", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "action",jsonrpc::JSON_STRING,"arguments",jsonrpc::JSON_STRING,"class_id",jsonrpc::JSON_STRING,"host_url",jsonrpc::JSON_STRING,"object_id",jsonrpc::JSON_STRING,"owner_vsID",jsonrpc::JSON_STRING, NULL), &hw3Server::Conflict_of_InterestI);
            this->bindAndAddMethod(jsonrpc::Procedure("OperatorEqEq", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "aPerson_class_id",jsonrpc::JSON_STRING,"aPerson_host_url",jsonrpc::JSON_STRING,"aPerson_object_id",jsonrpc::JSON_STRING,"aPerson_owner_vsID",jsonrpc::JSON_STRING,"action",jsonrpc::JSON_STRING,"arguments",jsonrpc::JSON_STRING,"class_id",jsonrpc::JSON_STRING,"host_url",jsonrpc::JSON_STRING,"object_id",jsonrpc::JSON_STRING,"owner_vsID",jsonrpc::JSON_STRING, NULL), &hw3Server::OperatorEqEqI);
            this->bindAndAddMethod(jsonrpc::Procedure("getVsID", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "action",jsonrpc::JSON_STRING,"arguments",jsonrpc::JSON_STRING,"class_id",jsonrpc::JSON_STRING,"host_url",jsonrpc::JSON_STRING,"object_id",jsonrpc::JSON_STRING,"owner_vsID",jsonrpc::JSON_STRING, NULL), &hw3Server::getVsIDI);
        }

        inline virtual void GetDistanceI(const Json::Value &request, Json::Value &response)
        {
            response = this->GetDistance(request["action"].asString(), request["arguments"].asString(), request["class_id"].asString(), request["host_url"].asString(), request["object_id"].asString(), request["owner_vsID"].asString());
        }
        inline virtual void Conflict_of_InterestI(const Json::Value &request, Json::Value &response)
        {
            response = this->Conflict_of_Interest(request["action"].asString(), request["arguments"].asString(), request["class_id"].asString(), request["host_url"].asString(), request["object_id"].asString(), request["owner_vsID"].asString());
        }
        inline virtual void OperatorEqEqI(const Json::Value &request, Json::Value &response)
        {
            response = this->OperatorEqEq(request["aPerson_class_id"].asString(), request["aPerson_host_url"].asString(), request["aPerson_object_id"].asString(), request["aPerson_owner_vsID"].asString(), request["action"].asString(), request["arguments"].asString(), request["class_id"].asString(), request["host_url"].asString(), request["object_id"].asString(), request["owner_vsID"].asString());
        }
        inline virtual void getVsIDI(const Json::Value &request, Json::Value &response)
        {
            response = this->getVsID(request["action"].asString(), request["arguments"].asString(), request["class_id"].asString(), request["host_url"].asString(), request["object_id"].asString(), request["owner_vsID"].asString());
        }
        virtual Json::Value GetDistance(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID) = 0;
        virtual Json::Value Conflict_of_Interest(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID) = 0;
        virtual Json::Value OperatorEqEq(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID) = 0;
        virtual Json::Value getVsID(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID) = 0;
};

#endif //JSONRPC_CPP_STUB_HW3SERVER_H_
