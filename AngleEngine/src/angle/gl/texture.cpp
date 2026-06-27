#include "texture.h"

Texture2D::Texture2D(const std::string& _Path) : m_Path{ _Path } {
	GL(glGenTextures(1, &m_ID));
	GL(glBindTexture(GL_TEXTURE_2D, m_ID));

	// Set (0;0) coord to left top
	stbi_set_flip_vertically_on_load(1);
	m_Data = stbi_load(_Path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_Data));

	GL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_Data)
		stbi_image_free(m_Data);
}

Texture2D::~Texture2D() {
	GL(glDeleteTextures(1, &m_ID));
}

// Bind texture with _Slot
void Texture2D::bind(unsigned int _Slot = 0) const {
	GL(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture2D::unbind() const {
	GL(glBindTexture(GL_TEXTURE_2D, 0));
}
