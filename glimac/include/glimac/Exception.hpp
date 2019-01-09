#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace glimac {
	/*! 
	\class Exception
	\brief A class derived of std::exception
	*/
	class Exception : public std::exception {
	public:
		
		Exception(const std::string &description, const std::string &file, const unsigned int line) noexcept
			: m_description(description), m_file(file), m_line(line)
		{
			m_what	= "-> Exception thrown from file " + m_file + " at line " + std::to_string(m_line)
					+ "\n---> " + m_description;
		}
		virtual ~Exception() noexcept {}

	public:
		const char *what() const noexcept override 
		{
			return m_what.c_str();
		}

	private:
		std::string m_description;
		std::string m_file;
		unsigned int m_line;
		std::string m_what;
	};
	
	#define THROW_EXCEPTION(str) throw Exception(str, __FILE__, __LINE__)
}