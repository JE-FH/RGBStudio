#pragma once
#include <vector>
#include <string>
#include "RGBLightRunnerAttributeDescription.hpp"

struct RGBLightRunnerTrigger {
	std::string id;
	std::vector<RGBLightRunnerAttributeDescription> attributes;
	std::vector<std::string> sub_triggers;
	MSGPACK_DEFINE_ARRAY(id, attributes, sub_triggers)
};