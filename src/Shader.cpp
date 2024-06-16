#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Constructs a Shader object and compiles the shader from the given file path.
 *
 * @param filePath Path to the shader file.
 */
Shader::Shader(const std::string& filePath)
	: m_filepath(filePath), m_rendererID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

/**
 * @brief Destroys the Shader object and deletes the shader program.
 */
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_rendererID));
}

/**
 * @brief Parses the shader file and extracts the vertex and fragment shader source code.
 *
 * @param filePath Path to the shader file.
 * @return ShaderProgramSource Struct containing vertex and fragment shader source code.
 */
ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class Shadertype
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2]; // 2 for vertex and fragment shaders
	Shadertype type = Shadertype::NONE;

	while (getline(stream, line))
	{
		// Set the type if #shader is found
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = Shadertype::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = Shadertype::FRAGMENT;
		}
		else // Add the line to the source
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

/**
 * @brief Compiles a shader of the given type from the source code.
 *
 * @param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
 * @param source The source code of the shader.
 * @return unsigned int The ID of the compiled shader.
 */
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); // Create the shader
	const char* src = source.c_str(); // Return the pointer of the first character of the source
	GLCall(glShaderSource(id, 1, &src, nullptr)); // Specify the shader source code
	GLCall(glCompileShader(id));

	// Error handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // Returns the compile status parameter
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char)); // Allocate this on the stack dynamically because 'char message[length]' is not allowed
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

/**
 * @brief Creates a shader program from the given vertex and fragment shader source code.
 *
 * @param vertexShader The source code of the vertex shader.
 * @param fragmentShader The source code of the fragment shader.
 * @return unsigned int The ID of the created shader program.
 */
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram(); // Create a shader program to attach shader to
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Attach both shaders to the program
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	GLCall(glLinkProgram(program)); // Link the program so the shaders are used
	GLCall(glValidateProgram(program)); // Check if the program can be executed

	// The shaders are linked to the program, so the shaders can be deleted
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

/**
 * @brief Binds the shader program for use.
 */
void Shader::Bind() const
{
	GLCall(glUseProgram(m_rendererID));
}

/**
 * @brief Unbinds the shader program.
 */
void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

/**
 * @brief Sets an integer uniform variable in the shader.
 *
 * @param name The name of the uniform variable.
 * @param value The integer value to set.
 */
void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

/**
 * @brief Sets a float uniform variable in the shader.
 *
 * @param name The name of the uniform variable.
 * @param value The float value to set.
 */
void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

/**
 * @brief Sets a vec4 uniform variable in the shader.
 *
 * @param name The name of the uniform variable.
 * @param v0 The first value of the vec4.
 * @param v1 The second value of the vec4.
 * @param v2 The third value of the vec4.
 * @param v3 The fourth value of the vec4.
 */
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

/**
 * @brief Sets a mat4 uniform variable in the shader.
 *
 * @param name The name of the uniform variable.
 * @param matrix The matrix to set.
 */
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

/**
 * @brief Retrieves the location of a uniform variable in the shader program.
 *
 * @param name The name of the uniform variable.
 * @return int The location of the uniform variable.
 */
int Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_uniformLocationCache[name] = location;
	return location;
}