#pragma once

#include <string>

class Texture
{
private:
	unsigned int RendererId;
	std::string FilePath;
	mutable int BindedSlot;
	unsigned char* LocalBuffer;
	int Width, Height, Bpp;//bits per pixel

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return Width; }
	inline int GetHeight() const { return Height; }
	inline int GetBindedSlot() const { return BindedSlot; }
};