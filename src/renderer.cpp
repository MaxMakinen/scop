/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:24 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 15:17:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "renderer.hpp"


void renderer::draw(const vertex_array &va, const index_buffer &ib, const shader &shader) const
{
	shader.bind();
	va.bind();
	ib.bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.get_count()/sizeof(int), GL_UNSIGNED_INT, nullptr));

}

void renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
