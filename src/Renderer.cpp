#include "Renderer.h"
#include <iostream>

/**
 * @brief Clears all OpenGL errors by calling glGetError until no errors are left.
 */
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

/**
 * @brief Logs OpenGL errors with details of the function, file, and line number.
 *
 * @param function The name of the function where the error occurred.
 * @param file The file where the error occurred.
 * @param line The line number where the error occurred.
 * @return true if no errors, false if there were errors.
 */
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
		return false;
	}

	return true;
}

/**
 * @brief Clears the screen by clearing the color buffer.
 */
void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

/**
 * @brief Draws the given vertex array and index buffer using the specified shader.
 *
 * @param va The vertex array to draw.
 * @param ib The index buffer to use for drawing.
 * @param shader The shader to use for drawing.
 */
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}