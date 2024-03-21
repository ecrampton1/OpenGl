#pragma once

#include "Renderer.hpp"

class Texture
{
private:
	unsigned int mRendererId;
	std::string mFilePath;
	unsigned char* mLocalBuffer;
	int mWidth, mHeight, mBpp;
public:
	Texture(const std::string& path);
	~Texture();

	//GPUs have slots for textures ( 8 -32) can ask platform for specifics
	void Bind(unsigned int slot=0) const;
	void UnBind();

	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }
};
