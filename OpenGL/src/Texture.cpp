#include "Texture.h"
#include "Renderer.h"
#include "GL/glew.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: RendererId(0), FilePath(path), BindedSlot(0), LocalBuffer(nullptr)
	, Width(0), Height(0), Bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(path.c_str(), &Width, &Height, &Bpp, 4);

	GLCall(glGenTextures(1, &RendererId));
	Bind();
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
	Unbind();

	if (LocalBuffer)
	{
		stbi_image_free(LocalBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &RendererId));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	BindedSlot = slot;
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererId));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0)); 
}
