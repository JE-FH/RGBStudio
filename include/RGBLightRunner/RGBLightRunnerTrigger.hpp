#pragma once
#include <vector>
#include <string>
#include "RGBLightRunnerAttributeDescription.hpp"

struct RGBLightRunnerTrigger {
	std::string id;
	std::vector<RGBLightRunnerAttributeDescription> attributes;
	MSGPACK_DEFINE_ARRAY(id, attributes)
};