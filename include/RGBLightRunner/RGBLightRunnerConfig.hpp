#pragma once
#include <vector>
#include <set>
#include <string>

struct InstanceDynamicAttribute {
	std::string name;
	std::string value;
	MSGPACK_DEFINE_ARRAY(name, value)
};

struct TriggerInstanceConfig {
	std::string triggerId;
	std::string instanceId;
	std::vector<InstanceDynamicAttribute> attributes;
	MSGPACK_DEFINE_ARRAY(triggerId, instanceId, attributes)

};

struct EffectInstanceConfig {
	std::string effectId;
	std::string instanceId;
	std::vector<InstanceDynamicAttribute> attributes;
	MSGPACK_DEFINE_ARRAY(effectId, instanceId, attributes)
};

struct RGBLightRunnerConfig {
	std::vector<TriggerInstanceConfig> triggerInstances;
	std::set<std::pair<std::string, std::string>> triggerActionEdges;
	std::set<std::pair<std::string, std::string>> actionEffectEdges;
	std::vector<EffectInstanceConfig> effectInstances;
	MSGPACK_DEFINE_ARRAY(triggerInstances, triggerActionEdges, actionEffectEdges, effectInstances)
};
