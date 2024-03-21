#ifndef __VERTEX_BUFFER_LAYOUT_HPP__
#define __VERTEX_BUFFER_LAYOUT_HPP__

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: 
			return 4;
		case GL_UNSIGNED_INT:
			return 2;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		printf("Incorrect Type\n");
		return 0;
	}
};

struct VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;
public:
	VertexBufferLayout() :
		mStride(0)
	{

	}

	template<class T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		mElements.push_back({ GL_FLOAT, count, GL_FALSE });
		mStride += VertexBufferElement::GetSizeOfType(GL_FLOAT)*count; //convert GL_FLOAT to a size to remove hardcodded
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		mStride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count; //convert GL_FLOAT to a size to remove hardcodded
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		mStride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count; //convert GL_FLOAT to a size to remove hardcodded
	}

	//ewww returns a copy of vector... (compiler might be smart enough to do ref
	inline const std::vector<VertexBufferElement> GetElementes() const { return mElements; }
	inline unsigned int GetStride() const { return mStride;  }

};

#endif
