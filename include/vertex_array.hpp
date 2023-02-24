/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_array.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 10:37:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_ARRAY_HPP
# define VERTEX_ARRAY_HPP

# include <GL/glew.h>
# include "error_handling.hpp"
# include "vertex_buffer.hpp"
# include "vertex_buffer_layout.hpp"

class vertex_array
{
	private:
		uint32_t m_renderer_id;
	public:
		vertex_array();
		~vertex_array();

		void add_buffer(const vertex_buffer &vb, const vertex_buffer_layout &layout);
		void bind() const;
		void unbind() const;
		void delete_buffer() const;
		void LinkAttrib(const vertex_buffer &vb, GLuint layout, GLuint numComp, GLenum type, GLsizeiptr stride, void *offset);

};

#endif
