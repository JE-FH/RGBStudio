#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "IConfigValueTypeDesc.hpp"

struct DynamicConfigSpecField {
	std::string name;
	bool required;
	std::unique_ptr<IConfigValueTypeDesc> type_desc;
};

class DynamicConfigSpec {
private:
	std::vector<DynamicConfigSpecField> fields;
public:
	void add_field(std::string name, std::unique_ptr<IConfigValueTypeDesc> type_desc, bool required);
	
	const std::vector<DynamicConfigSpecField>& get_fields() const;
};