#pragma once
#include <vector>
#include <string>
class IAssetLoader {
public:
	virtual ~IAssetLoader() {}
	virtual std::vector<char> load_asset(std::string asset_path) = 0;
};
