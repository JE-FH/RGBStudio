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
	std::vector<InstanceDynamicAttribute> attributes;
	MSGPACK_DEFINE_ARRAY(triggerId, attributes)

};

struct EffectInstanceConfig {
	std::string effectId;
	std::vector<InstanceDynamicAttribute> attributes;
	MSGPACK_DEFINE_ARRAY(effectId, attributes)
};

struct RGBLightRunnerConfig {
	std::vector<TriggerInstanceConfig> triggerInstances;
	std::set<std::pair<std::string, std::string>> triggerActionEdges;
	std::set<std::string> actions;
	std::set<std::pair<std::string, std::string>> actionEffectEdges;
	//Order is action, effectInstanceid, attribute name
	std::set<std::tuple<std::string, std::string, std::string>> actionAttributeEdges;
	std::vector<EffectInstanceConfig> effectInstances;
	MSGPACK_DEFINE_ARRAY(triggerInstances, triggerActionEdges, actions, actionEffectEdges, actionAttributeEdges, effectInstances)
};
