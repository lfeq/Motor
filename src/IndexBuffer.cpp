#include "IndexBuffer.h"
#include "Renderer.h"

/**
 * @brief Constructs an IndexBuffer and initializes it with data.
 *
 * @param data Pointer to the index data.
 * @param count Number of indices.
 */
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_count(count)
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

/**
 * @brief Destroys the IndexBuffer and cleans up the resources.
 */
IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID))
}

/**
 * @brief Binds the index buffer.
 */
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

/**
 * @brief Unbinds the index buffer.
 */
void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}