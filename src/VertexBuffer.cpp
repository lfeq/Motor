#include "VertexBuffer.h"
#include "Renderer.h"

/**
 * @brief Constructs a VertexBuffer object and initializes it with data.
 *
 * @param data Pointer to the vertex data.
 * @param size Size of the vertex data in bytes.
 */
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

/**
 * @brief Destructor for the VertexBuffer object. Deletes the vertex buffer object (VBO).
 */
VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

/**
 * @brief Binds the vertex buffer object (VBO).
 */
void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

/**
 * @brief Unbinds the vertex buffer object (VBO).
 */
void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}