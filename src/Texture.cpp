#include "Texture.h"
#include "stb_image/stb_image.h"

/**
 * @brief Constructs a Texture object, loads the image from the given path, and initializes the texture.
 *
 * @param path Path to the texture image file.
 */
Texture::Texture(const std::string& path)
	: m_rendererID(0), m_filepath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

	if (m_localBuffer == 0) {
		std::cout << "Texture not found!!!" << std::endl;
	}

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer) {
		stbi_image_free(m_localBuffer);
	}
}

/**
 * @brief Destructor for the Texture object. Deletes the texture from the GPU.
 */
Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

/**
 * @brief Binds the texture to a specified texture slot.
 *
 * @param slot The texture slot to bind the texture to (default is 0).
 */
void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

/**
 * @brief Unbinds the texture.
 */
void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}