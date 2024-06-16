#pragma once

#include <string>
#include "Renderer.h"

/**
 * @brief Texture class to manage OpenGL textures.
 */
class Texture {
private:
	unsigned int m_rendererID; ///< Renderer ID of the texture
	std::string m_filepath; ///< Filepath to the texture image
	unsigned char* m_localBuffer; ///< Local buffer to hold image data
	int m_width, m_height, m_BPP; ///< Width, height, and bytes per pixel of the texture

public:
	/**
	 * @brief Constructs a Texture object, loads the image from the given path, and initializes the texture.
	 *
	 * @param path Path to the texture image file.
	 */
	Texture(const std::string& path);

	/**
	 * @brief Destructor for the Texture object. Deletes the texture from the GPU.
	 */
	~Texture();

	/**
	 * @brief Binds the texture to a specified texture slot.
	 *
	 * @param slot The texture slot to bind the texture to (default is 0).
	 */
	void Bind(unsigned int slot = 0) const;

	/**
	 * @brief Unbinds the texture.
	 */
	void Unbind() const;

	inline int GetWidth() const { return m_width; } ///< Gets the width of the texture
	inline int GetHeight() const { return m_height; } ///< Gets the height of the texture
};
