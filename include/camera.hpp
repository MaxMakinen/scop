/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:37:17 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/28 18:27:21 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "vector.hpp"
# include "quaternion.hpp"
# include "shader.hpp"


class	camera
{
public:
	vec3f	position;
	vec3f	orientation = vec3f(0.f, 0.f, -1.f);
	vec3f	up = vec3f(0.f, 1.f, 0.f);

	int32_t	width;
	int32_t	height;

	bool	first_click = true;

	float	speed		= 0.1f;
	float	sensitivity	= 100.f;

	camera(int32_t width, int32_t height, vec3f position);

	void	matrix(float FOVdeg, float near_plane, float far_plane, shader &shader, const char *uniform);
	void	inputs(GLFWwindow *window);
};

#endif