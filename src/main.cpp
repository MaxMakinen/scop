/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:46 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 12:22:45 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "error_handling.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer_layout.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vector.hpp"
#include "mesh.hpp"

void controls(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	/* Initialise the GLFW library*/
	if (!glfwInit())
		return (-1);

	/* Tell GLFW what version of OpenGl We're using*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its openGL Context*/
	GLFWwindow *window = glfwCreateWindow(800, 600, "~ Scop ~", NULL ,NULL);
	if (window == NULL)
	{
		std::cout << "Error!: Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return (-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* initialize GLEW after creating a valid OpenGL rendering context. */
	if(glewInit() != GLEW_OK)
		std::cout << "Error!: glewInit not ok." << std::endl;

	/* Specify the wievport of OpenGL in the window.
	In this case the viewport goes from x = 0, y = 0 to x = 800, y = 600*/
	GLCall(glViewport(0, 0, 800, 600));

	/* Set framerate */
	//glfwSwapInterval(30);

	/* Set keyboard controls */
	glfwSetKeyCallback(window, controls);

	/* Get info of GPU and supported OpenGL vesion*/
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;

    // load resources, initialize the OpenGL states, ...

	GLfloat positions[] = {
		-100.f, -100.f, 0.0f, 0.0f, //0
		 100.f, -100.f, 1.0f, 0.0f, //1
		 100.f,  100.f, 1.0f, 1.0f, //2
		-100.f,  100.f, 0.0f, 1.0f  //3
	};

	unsigned int	indices[] = {
		0, 1, 2,
		2, 3, 0
	};


	// Vertices coordinates
	GLfloat vertices[] =
	{ //               COORDINATES                  /     COLORS           //
		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
	};
	
	// Indices for vertices order
	GLuint indices2[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};


	// Enable blending and set blending rules
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	vertex_array va;
	vertex_buffer vb(positions, 4 * 4 * sizeof(float));

	vertex_buffer_layout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.add_buffer(vb, layout);
//	va.LinkAttrib(vb, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *) 0);
//	va.LinkAttrib(vb, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

	index_buffer ib(indices, 6);

//	// Create projection matrix
//	mat4x4f proj;
//	//proj.ortho(-(window_size.x / 2.f), (window_size.x / 2.f), -(window_size.y / 2.f), (window_size.y / 2.f));
//	//proj.orthographic(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
//	proj.perspective(800, 600, 0.1f, 100.0f, 90.0f);
//	proj.invert();
//
//	// Create camera view matrix
//	mat4x4f view;
//	//view.lookat(vec3f(0.f, 0.f, -1.f), vec3f(0.f, 0.f, 0.f), vec3f(0.f, 1.f, 0.f));
//	view.translate(vec3f(0.f, 100.f, -20.f));
//
//	// Create model matrix;
//	mat4x4f model;
//	model.translate(vec3f(100.f, -50.f, 0.f));
//
//	// Create Model view matrix
//	mat4x4f mvp = proj * view * model;	

	// Load shaders
	shader shader("resources/shaders/basic.glsl");
	shader.bind();
	shader.set_uniform_4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
//	// Give shader transposed copy of matrix
//	shader.set_uniform_mat4f("u_MVP", mvp.transposed());
//	
//	// Load texture
//	texture texture("resources/textures/dickbutt.png");
//	texture.bind();
//	shader.set_uniform_1i("u_texture", 0);
//
//	va.unbind();
//	vb.unbind();
//	ib.unbind();
//	shader.unbind();
//	texture.unbind();

//	renderer renderer;
//	float r = 0.8f;
//	float increment = 0.05f;

	// Generates Vertex Array Object and binds it
	vertex_array VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	vertex_buffer VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	index_buffer EBO1(indices2, sizeof(indices2));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shader.get_id(), "scale");

	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.bind();
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so OpenGL knows to use it
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
//
//        // clear the buffers
//		renderer.clear();
//
//        // draw...
//		shader.bind();
//		texture.bind();
//		shader.set_uniform_4f("u_color", r, 0.3f, 0.8f, 1.0f);
//
//		renderer.draw(va, ib, shader);
//
//		if (r > 1.0f)
//			increment = -0.05f;
//		else if (r < 0.0f)
//			increment = 0.05f;
//		r += increment;
//        // end the current frame (internally swaps the front and back buffers)
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events*/
//		glfwPollEvents();
    }

    // Destroy window before ending program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending program
	glfwTerminate();
    return (0);
}
