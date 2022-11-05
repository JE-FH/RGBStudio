#pragma once
#include <stdexcept>
#include <string>

class AssetNotFoundError : std::exception {
private:
	std::string given_path;
	std::string indepth_explanation;
	std::string combined_reason;
public:
	AssetNotFoundError(std::string given_path, std::string indepth_explanation) {
		this->given_path = std::move(given_path);
		this->indepth_explanation = std::move(indepth_explanation);
		this->combined_reason = "AssetNotFoundError for " + this->given_path + "\n" + this->indepth_explanation;
	}

	const char* what();
};

