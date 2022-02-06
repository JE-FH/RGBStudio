#include "JSONRPC.hpp"
#include <iostream>
JSONRPC::JSONRPC(IJSONRPCConnection* conn)
{
	this->conn = std::move(conn);
	this->next_id = 0;
}

void JSONRPC::received_message(nlohmann::json message) {
	if (!message.is_object() || !message["method"].is_string() || !message["param"].is_object() || !message["id"].is_number_integer()) {
		std::cout << "missing fields in json" << std::endl;
		return;
	}
	notify_subs(message["id"], message["method"], message["param"]);
}

int JSONRPC::call(std::string method_name, nlohmann::json param) {
	conn->send_message({
		{"method", method_name},
		{"param", param},
		{"id", this->next_id}
	});
	return this->next_id++;
}

void JSONRPC::subscribe(IJSONRPCSubscriber& subscriber) {
	subscribers.insert(&subscriber);
}

void JSONRPC::unsubscribe(IJSONRPCSubscriber& unsubscriber)
{
	subscribers.erase(&unsubscriber);
}

void JSONRPC::notify_subs(int id, std::string method_name, nlohmann::json& param) {
	for (auto sub : subscribers) {
		sub->received_call(id, method_name, param);
	}
}
