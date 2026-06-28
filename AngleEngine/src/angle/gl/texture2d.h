#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "errors.h"
#include <string>

class API Texture2D {
private:
	unsigned int m_ID;
	std::string m_Path;
	int m_Width, m_Height;
	unsigned char* m_Data;

	// Bits Per Pixel
	int m_BPP;

public:
	Texture2D(const std::string& _Path);
	~Texture2D();

	// Bind texture with _Slot
	void bind(unsigned int _Slot = 0) const;
	void unbind() const;

	inline unsigned int get_width() const { return m_Width; }
	inline unsigned int get_height() const { return m_Height; }
	inline unsigned int get_bpp() const { return m_BPP; }
};

#endif // !__TEXTURE_H__