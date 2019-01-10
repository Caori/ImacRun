#include "glimac/AssetLoader.hpp"

namespace glimac {

	AssetLoader::AssetLoader() {
		std::cout << "AssetLoader constructor " << std::endl;
		loadAssets();
	}

	void AssetLoader::loadAssets() {
		std::cout << "AssetLoader : Load assets" << std::endl;

		// TODO : load actual assets for the game
		_models.insert(std::make_pair("coin", 			Model("coin", "tex1.jpeg")));
		_models.insert(std::make_pair("cat", 			Model("cat", "tex1.jpeg")));
		_models.insert(std::make_pair("tree",			Model("tree", "tex1.jpeg")));
		_models.insert(std::make_pair("bird",			Model("bird", "tex1.jpeg")));
		_models.insert(std::make_pair("barrel",			Model("barrel", "tex1.jpeg")));

		/*_textures.insert(std::make_pair("coin", 			Model("coin", "tex.jpg")));
		_textures.insert(std::make_pair("cat", 			Model("cat", "tex.jpg")));
		_textures.insert(std::make_pair("tree",			Model("tree", "tex.jpg")));
		_textures.insert(std::make_pair("bird",			Model("bird", "tex.jpg")));
		_textures.insert(std::make_pair("barrel",			Model("barrel", "tex.jpg")));*/
	}
}