#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

/**
 * @brief Constructs a VertexArray object and generates a new vertex array object (VAO).
 */
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

/**
 * @brief Destructor for the VertexArray object. Deletes the vertex array object (VAO).
 */
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

/**
 * @brief Adds a vertex buffer and its layout to the vertex array object (VAO).
 *
 * @param vb The VertexBuffer object to add.
 * @param layout The VertexBufferLayout object that describes the layout of the vertex buffer.
 */
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

/**
 * @brief Binds the vertex array object (VAO).
 */
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

/**
 * @brief Unbinds the vertex array object (VAO).
 */
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}