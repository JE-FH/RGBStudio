#pragma once
struct RGBLightRunnerAttributeDescription {
	std::string name;
	std::string type;
	MSGPACK_DEFINE_ARRAY(name, type)
};