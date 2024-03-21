#include "VertexArray.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mRendererId); //vertex array object not created with core
	
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mRendererId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElementes();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i); //enable the vertex ? ok then
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),(const void*) offset);  //index 0 vertex array to currently bound buffer so vao is linked to buffer.
		offset += element.count*VertexBufferElement::GetSizeOfType(element.type);
	}
	
}

void VertexArray::Bind() const
{
	glBindVertexArray(mRendererId);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
