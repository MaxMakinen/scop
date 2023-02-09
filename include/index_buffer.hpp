/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_buffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 13:12:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INDEX_BUFFER_HPP
# define INDEX_BUFFER_HPP

# include "scop.hpp"

class index_buffer
{
	private:
		GLuint m_Renderer_id;
		GLuint m_Count;
	public:
		index_buffer(const GLuint *data, GLuint count);
		~index_buffer();

		void bind() const;
		void unbind() const;

		inline GLuint get_count() const { return (m_Count); }
};

#endif
