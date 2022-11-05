#pragma once
#include <string>
#include <rpc/client.h>
#include "RGBLightRunner/HelloResponse.hpp"
#include "RGBLightRunner/RGBLightRunnerConfig.hpp"
#include "RGBLightRunner/RGBLightRunnerTrigger.hpp"
#include "RGBLightRunner/RGBLightRunnerEffect.hpp"

class LightRunnerApi {
private:
	std::string _address;
	unsigned short _port;
	rpc::client _client;
public:
	LightRunnerApi(std::string address, unsigned short port);
	
	HelloResponse Hello();

	std::vector<RGBLightRunnerTrigger> ListTriggers();
	
	std::vector<RGBLightRunnerEffect> ListEffects();

	void ApplyConfig(RGBLightRunnerConfig config);
};