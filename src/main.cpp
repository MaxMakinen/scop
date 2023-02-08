#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "scop.hpp"

static void	GLClearError()
{
	while(glGetError() != GL_NO_ERROR); // GL_NO_ERROR guaranteed to be 0. so could be !glGetError()
}

static void	GLCheckError()
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
	}
}

struct	ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath)
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
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str()};
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

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,
	};

	unsigned int	indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);



	ShaderProgramSource source = ParseShader("../resources/shaders/basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	glUseProgram(shader);

    // run the main loop
    bool running = true;
    while (running)
    {

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
		GLClearError(); // Clear the Error messages so that we dont find anything old.
		glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr); // GL_INT invalid input. All arrays MUST be unsigned int.
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		GLCheckError(); // Print any and all Error messages that occured sinde GLClearError();

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