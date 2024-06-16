#pragma once

/**
 * @brief VertexBuffer class to manage OpenGL vertex buffer objects (VBOs).
 */
class VertexBuffer {
private:
	unsigned int m_rendererID; ///< Renderer ID of the vertex buffer object

public:
	/**
	 * @brief Constructs a VertexBuffer object and initializes it with data.
	 *
	 * @param data Pointer to the vertex data.
	 * @param size Size of the vertex data in bytes.
	 */
	VertexBuffer(const void* data, unsigned int size);

	/**
	 * @brief Destructor for the VertexBuffer object. Deletes the vertex buffer object (VBO).
	 */
	~VertexBuffer();

	/**
	 * @brief Binds the vertex buffer object (VBO).
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the vertex buffer object (VBO).
	 */
	void Unbind() const;
};
