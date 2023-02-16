/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:00:06 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/10 09:00:07 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP
# include <string>
# include <unordered_map>
# include "vector.hpp"

struct	shader_program_source
{
	std::string vertex_source;
	std::string fragment_source;
};

class shader
{
	private:
		std::string m_filepath;
		uint32_t m_renderer_id;
		//caching for uniforms
		std::unordered_map<std::string, int32_t> m_uniform_location_cache;

	public:
		shader(const std::string &filepath);
		~shader();

		void bind() const;
		void unbind() const;

		//set uniforms
		void set_uniform_1i(const std::string &name, int32_t v);
		void set_uniform_1f(const std::string &name, float v);
		void set_uniform_4f(const std::string &name, float v0, float v1, float f2, float f3);
		void set_uniform_mat4f(const std::string &name, const mat4x4f &matrix);

	private:
		shader_program_source parse_shader(const std::string &filepath);
		uint32_t compile_shader(uint32_t type, const std::string &source);
		uint32_t create_shader(const std::string &vertexShader, const std::string &fragmentShader);
		int32_t get_uniform_location(const std::string &name);
};

#endif