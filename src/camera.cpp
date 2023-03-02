/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:46:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/03/02 15:07:10 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <GL/glew.h>
# include <GLFW/glfw3.h>

#include "camera.hpp"

camera::camera(int32_t width, int32_t height, vec3f position)
{
	camera::width		= width;
	camera::height		= height;
	camera::position	= position;
	camera::old_time	= glfwGetTime();
}

float	camera::elapsed_time() 
{
	float time = glfwGetTime();
	float elapsed = time - old_time;
	camera::old_time = time;

	return (elapsed); 
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
	glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), uniform), 1, GL_TRUE, &camera[0][0]);
}

void	camera::inputs(GLFWwindow *window)
{
	float	delta_time = elapsed_time();
	vec3f	newOrientation;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position = position + speed * delta_time * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newOrientation = orientation.cross_product(up);
		newOrientation.normalize();
		position = position + speed * delta_time * -newOrientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position = position + speed * delta_time * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newOrientation = orientation.cross_product(up);
		newOrientation.normalize();
		position = position + speed * delta_time * newOrientation;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position = position + speed * delta_time * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position = position + speed * delta_time * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 4.f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		speed = 1.f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//	if (first_click == true)
	//	{
	//		glfwSetCursorPos(window, (width * 0.5f), (height * 0.5f));
	//		first_click = false;
	//	}

		double mouseX;
		double mouseY;
		mat4x4f	rot_matrix;
		mat4x4f	rot_matrix_x;
		mat4x4f	rot_matrix_y;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = (sensitivity * (float)(mouseY - (height / 2)) / height);// * 0.01745329251f;
		float rotY = (sensitivity * (float)(mouseX - (width / 2)) / width);// * 0.01745329251f;

		rot_matrix_x.make_rotate_x(-(rotX * 0.01745329251f));
		rot_matrix_y.make_rotate_y(rotY * 0.01745329251f);

		rot_matrix_x.multiply(rot_matrix_y, rot_matrix_x, rot_matrix);
		rot_matrix.mult_dir_matrix(orientation, newOrientation);

		orientation = newOrientation.normalize();

		//glfwSetCursorPos(window, (width * 0.5f), (height * 0.5f));
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		first_click = true;
	}
}