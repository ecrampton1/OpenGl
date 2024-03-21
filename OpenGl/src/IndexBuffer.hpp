#ifndef __INDEX__BUFFER__HPP__
#define __INDEX__BUFFER__HPP__



class IndexBuffer
{
private:
	unsigned int mRendererID;
	unsigned int mCount;

	//use 16 bit as it be better yo
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	//inline really necessary
	inline unsigned int GetCount() const { return mCount; }
};


#endif