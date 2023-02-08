#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/scop.hpp"


static void ParseShader(const std::string &filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				//set mode to vertex
			else if (line.find("fragment") != std::string::npos)
				//set mode to fragment
		}
	}
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
	unsigned int	id = glCreateShader(type);
	const char		*src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int	result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char message[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return (0);
	}

	return (id);
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	unsigned int	program = glCreateProgram();
	unsigned int	vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int	fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return (program);
}

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

	// initialize GLEW after creating a valid OpenGL rendering context. Automatically done by SFML in previous command
	if(glewInit() != GLEW_OK)
		std::cout << "Error!: glewInit not ok" << std::endl;

    // load resources, initialize the OpenGL states, ...

	float positions[6] = {
		-0.5, -0.5f,
		0.0, 0.5f,
		0.5, -0.5f,
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

    // run the main loop
    bool running = true;
    while (running)
    {

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
		glDrawArrays(GL_TRIANGLES, 0, 3);

        // end the current frame (internally swaps the front and back buffers)
        window.display();

        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				running = false;
				break;
			}
            else if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
    }

    // release resources...
	glDeleteProgram(shader);
	window.setActive(false);

    return (0);
}