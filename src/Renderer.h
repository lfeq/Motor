#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak(); // Break debugging if x returns false
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__)); // Wrap a function with an error boundary

/**
 * @brief Clears all OpenGL errors.
 */
void GLClearError();

/**
 * @brief Logs OpenGL errors with details of the function, file, and line number..
 *
 * @param function The name of the function where the error occurred.
 * @param file The file where the error occurred.
 * @param line The line number where the error occurred.
 * @return true if no errors, false if there were errors.
 */
bool GLLogCall(const char* function, const char* file, int line);

/**
 * @brief Renderer class that handles rendering operations.
 */
class Renderer {
public:
	/**
	 * @brief Clears the screen.
	 */
	void Clear() const;

	/**
	 * @brief Draws the given vertex array and index buffer using the specified shader.
	 *
	 * @param va The vertex array to draw.
	 * @param ib The index buffer to use for drawing.
	 * @param shader The shader to use for drawing.
	 */
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};