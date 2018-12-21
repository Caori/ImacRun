#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

namespace glimac{
	std::string readFile(const char *filePath);
	GLuint LoadShader(const char *vertex_path, const char *fragment_path);
}