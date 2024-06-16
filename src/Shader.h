#pragma once

#include <iostream>
#include <unordered_map>
#include "glm/glm.hpp"

/**
 * @brief Structure to hold vertex and fragment shader source code.
 */
struct ShaderProgramSource {
	std::string VertexSource; ///< Source code of the vertex shader
	std::string FragmentSource; ///< Source code of the fragment shader
};

/**
 * @brief Shader class to manage OpenGL shaders.
 */
class Shader {
private:
	unsigned int m_rendererID; ///< Renderer ID of the shader program
	std::string m_filepath; ///< Filepath to the shader source file
	std::unordered_map<std::string, int> m_uniformLocationCache; ///< Cache for uniform locations

public:
	/**
	 * @brief Constructs a Shader object and compiles the shader from the given file path.
	 *
	 * @param filepath Path to the shader file.
	 */
	Shader(const std::string& filepath);

	/**
	 * @brief Destroys the Shader object and deletes the shader program.
	 */
	~Shader();

	/**
	 * @brief Binds the shader program for use.
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the shader program.
	 */
	void Unbind() const;

	/**
	 * @brief Sets an integer uniform variable in the shader.
	 *
	 * @param name The name of the uniform variable.
	 * @param value The integer value to set.
	 */
	void SetUniform1i(const std::string& name, int value);

	/**
	 * @brief Sets a float uniform variable in the shader.
	 *
	 * @param name The name of the uniform variable.
	 * @param value The float value to set.
	 */
	void SetUniform1f(const std::string& name, float value);

	/**
	 * @brief Sets a vec4 uniform variable in the shader.
	 *
	 * @param name The name of the uniform variable.
	 * @param v0 The first component of the vec4.
	 * @param v1 The second component of the vec4.
	 * @param v2 The third component of the vec4.
	 * @param v3 The fourth component of the vec4.
	 */
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	/**
	 * @brief Sets a mat4 uniform variable in the shader.
	 *
	 * @param name The name of the uniform variable.
	 * @param matrix The matrix to set.
	 */
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	/**
	 * @brief Parses the shader file and extracts the vertex and fragment shader source code.
	 *
	 * @param filepath Path to the shader file.
	 * @return ShaderProgramSource Struct containing vertex and fragment shader source code.
	 */
	ShaderProgramSource ParseShader(const std::string& filepath);

	/**
	 * @brief Compiles a shader of the given type from the source code.
	 *
	 * @param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
	 * @param source The source code of the shader.
	 * @return unsigned int The ID of the compiled shader.
	 */
	unsigned int CompileShader(unsigned int type, const std::string& source);

	/**
	 * @brief Creates a shader program from the given vertex and fragment shader source code.
	 *
	 * @param vertexShader The source code of the vertex shader.
	 * @param fragmentShader The source code of the fragment shader.
	 * @return unsigned int The ID of the created shader program.
	 */
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	/**
	 * @brief Retrieves the location of a uniform variable in the shader program.
	 *
	 * @param name The name of the uniform variable.
	 * @return int The location of the uniform variable.
	 */
	int GetUniformLocation(const std::string& name);
};
