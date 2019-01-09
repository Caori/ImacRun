#pragma once

#include "common.hpp"
#include <glimac/FilePath.hpp>
#include <SDL/SDL.h>

namespace glimac {

	/// \brief class wich represents the Parameters
	class Parameters {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		Parameters() {};
		/// \brief private destructor
		~Parameters() {};

	public:
		/// \brief access the singleton instance
		static Parameters& instance() {
			static Parameters instance;
			return instance;
		}
		// prevent copy
		Parameters(const Parameters&) = delete;
	    Parameters(Parameters&&) = delete;
	    Parameters& operator=(const Parameters&) = delete;
	    Parameters& operator=(Parameters&&) = delete;

		// CONST GETTERS
		/// \brief get the time difference in seconds between the current frame and the previous (enforced)
		float deltaTime() const { return _deltaTime; };

		/// \brief get the application path
		const glimac::FilePath& appPath() const { return _appPath; };
		
		/// \brief get the frame rate
		const Uint32 framerate() const { return _framerate_ms; };

		// NON-CONST GETTERS (can be used as setters)
		/// \brief set the application path
		glimac::FilePath& appPath() { return _appPath; };

		/// \brief get the running speed
		const float getSpeed(){
			return _speed;
		}
		
	// MEMBERS
	private:
		// CONSTANTS
		/// \brief path of the app
		glimac::FilePath _appPath;
		const uint32_t _windowWidth = 1200;
		const uint32_t _windowHeight = 900;
		/// \brief time between 2 frames (ms)
		const Uint32 _framerate_ms = 1000 / 30;
		/// \brief time between 2 frames (seconds)
		const float _deltaTime = 1.f/30.f;
		/// \brief running speed
		const float _speed = 0.1;
	};
}
