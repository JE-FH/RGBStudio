#pragma once
#include "IAssetLoader.hpp"
#include <filesystem>

class FSAssetLoader : public IAssetLoader {
private:
	std::filesystem::path base_path;
public:
	FSAssetLoader(std::string base_path);

	std::vector<char> load_asset(std::string asset_path) override;
};
