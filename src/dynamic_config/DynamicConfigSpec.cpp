#include <dynamic_config/DynamicConfigSpec.hpp>

void DynamicConfigSpec::add_field(std::string name, std::unique_ptr<IConfigValueTypeDesc> type_desc, bool required)
{
	fields.push_back(DynamicConfigSpecField{
		.name = std::move(name),
		.required = required,
		.type_desc = std::move(type_desc)
	});
}

const std::vector<DynamicConfigSpecField>& DynamicConfigSpec::get_fields() const {
	return fields;
}
