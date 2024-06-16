#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

/**
 * @brief VertexArray class to manage OpenGL vertex array objects (VAOs).
 */
class VertexArray {
private:
	unsigned int m_rendererID; ///< Renderer ID of the vertex array object

public:
	/**
	 * @brief Constructs a VertexArray object and generates a new vertex array object (VAO).
	 */
	VertexArray();

	/**
	 * @brief Destructor for the VertexArray object. Deletes the vertex array object (VAO).
	 */
	~VertexArray();

	/**
	 * @brief Adds a vertex buffer and its layout to the vertex array object (VAO).
	 *
	 * @param vb The VertexBuffer object to add.
	 * @param layout The VertexBufferLayout object that describes the layout of the vertex buffer.
	 */
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	/**
	 * @brief Binds the vertex array object (VAO).
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the vertex array object (VAO).
	 */
	void Unbind() const;
};
