#include "FSAssetLoader.hpp"
#include "GenericAssetLoaderErrors.hpp"
#include <fstream>
namespace fs = std::filesystem;

FSAssetLoader::FSAssetLoader(std::string base_path) {
	this->base_path = fs::path(std::move(base_path));
}

std::vector<char> FSAssetLoader::load_asset(std::string asset_path) {
	auto real_path = this->base_path / asset_path;

	std::ifstream t(real_path);

	if (!t.is_open()) {
		throw AssetNotFoundError(asset_path, "file was not found at " + real_path.string());
	}

	std::vector<char> buffer;

	t.seekg(0, std::ios::end);
	buffer.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	buffer.assign(
		(std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>()
	);

	return buffer;
}
