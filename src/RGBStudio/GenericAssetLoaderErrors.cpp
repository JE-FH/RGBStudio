#include "GenericAssetLoaderErrors.hpp"

AssetNotFoundError::AssetNotFoundError(std::string given_path, std::string indepth_explanation) {
	this->given_path = std::move(given_path);
	this->indepth_explanation = std::move(indepth_explanation);
	this->combined_reason = "AssetNotFoundError for " + this->given_path + "\n" + this->indepth_explanation;
}

const char* AssetNotFoundError::what() {
	return combined_reason.c_str();
}
