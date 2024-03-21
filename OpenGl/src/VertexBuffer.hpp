#ifndef __VERTEX__BUFFER__HPP__
#define __VERTEX__BUFFER__HPP__



class VertexBuffer
{
private:
	unsigned int mRendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};


#endif