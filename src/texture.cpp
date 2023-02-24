/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:58:42 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 15:35:29 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.hpp"

texture::texture(const std::string &path)
	: m_renderer_id(0), m_filepath(path), m_localbuffer(nullptr), 
	m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(true);
	m_localbuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
	GLCall(glGenTextures(1, &m_renderer_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

	// Configures the type of algorithm that is used to make the image smaller or bigger
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Configures the way the texture repeats (if it does at all)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	/* If GL_CLAMP_TO_BORDER choose a border color*/
	//	float border_color[] = {1.f, 1.f, 0.8f, 1.0f};
	//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);


	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer));
	// Generate MipMap in case surface gets further from camera
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localbuffer)
	{
		stbi_image_free(m_localbuffer);
	}
}

texture::~texture()
{
	GLCall(glDeleteTextures(1, &m_renderer_id));
}

void texture::texUnit(shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.get_id(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.bind();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void texture::bind(uint32_t slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
