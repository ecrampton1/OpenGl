#include "Texture.hpp"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	: mFilePath(path), mLocalBuffer(nullptr),mWidth(0),mHeight(0), mBpp(0)
{
	//flips it upside down expects it to start bottom left when loading
	stbi_set_flip_vertically_on_load(1);
	mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBpp, 4);
	
	glGenTextures(1, &mRendererId);
	glBindTexture(GL_TEXTURE_2D, mRendererId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//internal format (stored) vs format (input format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);
	UnBind();

	if (mLocalBuffer)
		stbi_image_free(mLocalBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mRendererId);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, mRendererId );
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
