#pragma once

#include <iostream>
#include <map>
#include "glimac/Model.hpp"
#include "glimac/Texture.hpp"

namespace glimac {

	/// \brief singleton class wich manages the assets for everyone to access them 
	class AssetLoader {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		AssetLoader();

		/// \brief private destructor
		~AssetLoader()
		{};

	public:
		/// \brief access the singleton instance
		static AssetLoader& instance() {
			static AssetLoader instance;
			return instance;
		}
		// prevent copy
		AssetLoader(const AssetLoader&) = delete;
	    AssetLoader(AssetLoader&&) = delete;
	    AssetLoader& operator=(const AssetLoader&) = delete;
	    AssetLoader& operator=(AssetLoader&&) = delete;

	public:
		// CONST GETTERS
		const std::map<std::string, Model>& models() const {
			return _models;
		}

		// NON-CONST GETTERS
		std::map<std::string, Model>& models() {
			return _models;
		}

	private:
		// METHODS
		void loadAssets();

		// MEMBERS
		/// \brief 3D models assets
		std::map<std::string, Model> _models;

		//TODO : add this stuff

		/// \brief textures assets
		//std::map<int, Texture> _textures;
	};

}