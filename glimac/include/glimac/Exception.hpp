#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace glimac
{
	// Je ne mets pas de code d'erreur ni de niveau d'erreur
	class MyException : public std::exception
	{
	public:
		
		MyException(const std::string &description, const std::string &file, const unsigned int line) noexcept
			: m_description(description), m_file(file), m_line(line)
		{
			m_what	= "-> Exception thrown from file " + m_file + " at line " + std::to_string(m_line)
					+ "\n---> " + m_description;
		}
		virtual ~MyException() noexcept {}

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
	
	// On est oblig� d'utiliser une macro pour s'assurer que le code est bien recopi� par le compilateur
	// On n'utilise pas une fonction inline car rien ne garantit que le compilateur va la recopier
	// Si elle n'est pas recopi�e, __FILE__ et __LINE__ donneraient : "my_exception.hpp" et "38"
	#define THROW_EXCEPTION(str) throw MyException(str, __FILE__, __LINE__)
}



