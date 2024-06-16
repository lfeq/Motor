#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

/**
 * @brief Struct describing a single element in a vertex buffer.
 */
struct VertexBufferElement {
	unsigned int type;         ///< OpenGL type of the element (e.g., GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE).
	unsigned int count;        ///< Number of elements (e.g., 1 for scalar, 2 for vec2, etc.).
	unsigned char normalized;  ///< Whether the data should be normalized.

	/**
	 * @brief Gets the size of the specified OpenGL type.
	 *
	 * @param type OpenGL type for which to determine the size.
	 * @return Size of the OpenGL type in bytes.
	 */
	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:          return 4;
		case GL_UNSIGNED_INT:   return 4;
		case GL_UNSIGNED_BYTE:  return 1;
		}
		ASSERT(false); // Unknown type
		return 0;
	}
};

/**
 * @brief Class representing the layout of a vertex buffer.
 */
class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_elements; ///< Elements in the vertex buffer layout.
	unsigned int m_stride;                      ///< Total stride of the vertex buffer layout.

public:
	/**
	 * @brief Constructs a VertexBufferLayout object.
	 */
	VertexBufferLayout()
		: m_stride(0) {}

	/**
	 * @brief Adds a new element to the vertex buffer layout.
	 *
	 * @tparam T Data type of the element (e.g., float, unsigned int, unsigned char).
	 * @param count Number of elements (e.g., 1 for scalar, 2 for vec2, etc.).
	 */
	template<typename T>
	void Push(unsigned int count) {
		static_assert(false); // Invalid type
	}

	/**
	 * @brief Adds a float element to the vertex buffer layout.
	 *
	 * @param count Number of float elements.
	 */
	template<>
	void Push<float>(unsigned int count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	/**
	 * @brief Adds an unsigned int element to the vertex buffer layout.
	 *
	 * @param count Number of unsigned int elements.
	 */
	template<>
	void Push<unsigned int>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/**
	 * @brief Adds an unsigned char element to the vertex buffer layout.
	 *
	 * @param count Number of unsigned char elements.
	 */
	template<>
	void Push<unsigned char>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	/**
	 * @brief Gets the elements in the vertex buffer layout.
	 *
	 * @return Const reference to the vector of VertexBufferElement.
	 */
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }

	/**
	 * @brief Gets the stride of the vertex buffer layout.
	 *
	 * @return Stride of the vertex buffer layout in bytes.
	 */
	inline unsigned int GetStride() const { return m_stride; }
};
