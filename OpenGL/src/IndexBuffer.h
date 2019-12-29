#pragma once

class IndexBuffer
{
private:
	unsigned int RendererId;
	unsigned int Count;

public:
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return Count; }
};