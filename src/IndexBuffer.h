#pragma once

/**
 * @brief IndexBuffer class that manages an OpenGL index buffer.
 */
class IndexBuffer {
private:
	/// Renderer ID for the OpenGL index buffer.
	unsigned int m_rendererID;
	/// Number of indices in the buffer.
	unsigned int m_count;
public:
	/**
	 * @brief Constructs an IndexBuffer and initializes it with data.
	 *
	 * @param data Pointer to the index data.
	 * @param count Number of indices.
	 */
	IndexBuffer(const unsigned int* data, unsigned int count);

	/**
	 * @brief Destroys the IndexBuffer and cleans up the resources.
	 */
	~IndexBuffer();

	/**
	 * @brief Binds the index buffer.
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the index buffer.
	 */
	void Unbind() const;

	/**
	 * @brief Gets the number of indices in the buffer.
	 *
	 * @return unsigned int Number of indices.
	 */
	inline unsigned int GetCount() const { return m_count; }
};