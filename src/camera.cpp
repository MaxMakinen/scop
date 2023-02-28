/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:46:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/28 15:18:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <GL/glew.h>
# include <GLFW/glfw3.h>

#include "camera.hpp"

camera::camera(int32_t width, int32_t height, vec3f position)
{
	camera::width = width;
	camera::height = height;
	camera::position = position;
}

void	camera::matrix(float FOVdeg, float near_plane, float far_plane, shader &shader, const char *uniform)
{
	mat4x4f	view;
	mat4x4f	projection;
	mat4x4f	camera;

	view.lookat(position, position + orientation, up);
	
	/* FOVdeg turned to radians by FOVdeg * M_PI / 180 = FOVdeg * 0.01745329251f */
	projection.perspective((float)(width / height), near_plane, far_plane, FOVdeg * 0.01745329251f);
	camera.multiply(projection, view, camera);
	projection = projection * view;
	glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), uniform), 1, GL_FALSE, &projection[0][0]);
}

void	camera::inputs(GLFWwindow *window)
{
	;
}