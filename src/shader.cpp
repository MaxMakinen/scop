/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:00:16 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/10 09:00:29 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "error_handling.hpp"
#include "shader.hpp"

shader::shader(const std::string &filepath)
	: m_filepath(filepath), m_renderer_id(0)
{
	shader_program_source source = parse_shader(filepath);
	m_renderer_id = create_shader(source.vertex_source, source.fragment_source);
}

shader::~shader()
{
	GLCall(glDeleteProgram(m_renderer_id));
}

void shader::bind() const
{
	GLCall(glUseProgram(m_renderer_id));
}


void shader::unbind() const
{
	GLCall(glUseProgram(0));
}

void shader::set_uniform_1i(const std::string &name, int32_t value)
{
	GLCall(glUniform1i(get_uniform_location(name), value));
}

void shader::set_uniform_1f(const std::string &name, float value)
{
	GLCall(glUniform1f(get_uniform_location(name), value));
}

void shader::set_uniform_4f(const std::string &name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
}

int32_t shader::get_uniform_location(const std::string &name)
{
	if ( m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
	{
		return (m_uniform_location_cache[name]);
	}

	int32_t location;
	GLCall(location = glGetUniformLocation(m_renderer_id, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	m_uniform_location_cache[name] = location;
	return (location);
}

shader_program_source shader::parse_shader(const std::string &filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

uint32_t shader::compile_shader(uint32_t type, const std::string &source)
{
	uint32_t	id; 
	const char		*src;
	int32_t			result;
	int32_t			length;
	char			*message;
	
	length = 0;
	src = source.c_str();
	GLCall(id = glCreateShader(type));
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		message = (char *)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return (0);
	}

	return (id);
}

uint32_t shader::create_shader(const std::string &vertexShader, const std::string &fragmentShader)
{
	uint32_t	program; 
	GLCall( program = glCreateProgram());
	uint32_t	vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
	uint32_t	fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return (program);
}