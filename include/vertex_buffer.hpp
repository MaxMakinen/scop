/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 11:23:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VERTEX_BUFFER_HPP
# define VERTEX_BUFFER_HPP

# include <GL/glew.h>
# include "error_handling.hpp"

class vertex_buffer
{
	private:
		GLuint m_Renderer_id;
	public:
		vertex_buffer(const GLfloat *vertices, uint32_t size);
		~vertex_buffer();

		void bind() const;
		void unbind() const;
		void delete_buffer() const;
};

#endif
