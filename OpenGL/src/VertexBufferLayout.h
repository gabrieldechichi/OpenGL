#pragma once

#include <vector>

struct VertexBufferLayoutElement
{
	unsigned int Type;
	unsigned int TypeSize;
	unsigned int Count;
	unsigned int Normalized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferLayoutElement> Elements;
	unsigned int Stride;

public:
	VertexBufferLayout() : Stride(0) {}

	void PushFloat(unsigned int count);
	void PushInt(unsigned int count);
	void PushByte(unsigned int count);

	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return Elements; }
	inline unsigned int GetSride() const { return Stride; }

private:
	void Push_Internal(unsigned int type, unsigned int typeSize, unsigned int count, bool normalized = false);
};