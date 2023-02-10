/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:58:51 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/10 12:58:52 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "error_handling.hpp"
# include <string>
#include "../include/vendor/stb_image/stb_image.h"

class texture
{
	private:
		uint32_t		m_renderer_id;
		std::string		m_filepath;
		unsigned char	*m_localbuffer;
		int32_t			m_width;
		int32_t			m_height;
		int32_t			m_bpp;
	public:
		texture(const std::string &path);
		~texture();

		void bind(uint32_t slot = 0) const;
		void unbind() const;

		inline int32_t get_width() const { return (m_width); }
		inline int32_t get_height() const { return (m_height); }
};

#endif