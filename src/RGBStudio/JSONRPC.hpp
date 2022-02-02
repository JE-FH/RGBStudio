#pragma once
#include <nlohmann/json.hpp>
#include <set>
class IJSONRPCConnection {
public:
	virtual void send_message(nlohmann::json message) = 0;
};

class IJSONRPCSubscriber {
public:
	virtual void received_call(int id, std::string method_name, nlohmann::json param) = 0;
};

class JSONRPC {
public:
	JSONRPC(IJSONRPCConnection* conn);
	void received_message(nlohmann::json message);
	int call(std::string method_name, nlohmann::json param);
	void subscribe(IJSONRPCSubscriber& subscriber);
	void unsubscribe(IJSONRPCSubscriber& unsubscriber);
private:
	void notify_subs(int id, std::string method_name, nlohmann::json& param);
	std::set<IJSONRPCSubscriber*> subscribers;
	IJSONRPCConnection* conn;
	int next_id;
};
