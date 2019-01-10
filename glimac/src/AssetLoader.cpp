#include "glimac/AssetLoader.hpp"

namespace glimac {

	AssetLoader::AssetLoader() {
		std::cout << "AssetLoader constructor " << std::endl;
		loadAssets();
	}

	void AssetLoader::loadAssets() {
		std::cout << "AssetLoader : Load assets" << std::endl;

<<<<<<< HEAD
		_models.insert(std::make_pair("menu", 			Model("menu", "Menu-player.png")));
=======
>>>>>>> f15a6f1ffbcd57156249c656d48f58d8792c6c89
		_models.insert(std::make_pair("coin", 			Model("coin", "metal.jpeg")));
		_models.insert(std::make_pair("cat", 			Model("cat", "sky.jpeg")));
		_models.insert(std::make_pair("bird",			Model("bird", "feathers.jpeg")));
		_models.insert(std::make_pair("barrel",			Model("barrel", "wood.jpeg")));
		_models.insert(std::make_pair("cube",			Model("cube", "snow.jpeg")));
		_models.insert(std::make_pair("wolf",			Model("wolf", "sky.jpeg")));
		_models.insert(std::make_pair("rock",			Model("rock", "rock.jpeg")));
	}
}