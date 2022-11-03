#include "LightRunnerApi.hpp"

LightRunnerApi::LightRunnerApi(std::string address, unsigned short port)
	: _client(address, port) 
{ 
	_address = address;
	_port = port;
}

HelloResponse LightRunnerApi::Hello()
{
	return _client.call("Hello").as<HelloResponse>();
}

std::vector<RGBLightRunnerTrigger> LightRunnerApi::ListTriggers() {
	return _client.call("ListTriggers").as<std::vector<RGBLightRunnerTrigger>>();
}

std::vector<RGBLightRunnerEffect> LightRunnerApi::ListEffects() {
	return _client.call("ListEffects").as<std::vector<RGBLightRunnerEffect>>();
}