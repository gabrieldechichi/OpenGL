#include "VertexBufferLayout.h"
#include "GL/glew.h"

void VertexBufferLayout::PushFloat(unsigned int count)
{
	Push_Internal(GL_FLOAT, sizeof(GLfloat), count);
}

void VertexBufferLayout::PushInt(unsigned int count)
{
	Push_Internal(GL_UNSIGNED_INT, sizeof(GLuint), count);
}

void VertexBufferLayout::PushByte(unsigned int count)
{
	Push_Internal(GL_UNSIGNED_BYTE, sizeof(GLbyte), count);
}

void VertexBufferLayout::Push_Internal(unsigned int type, unsigned int typeSize, unsigned int count, bool normalized)
{
	unsigned int glNormalized = normalized ? GL_TRUE : GL_FALSE;
	Elements.push_back({ type, typeSize, count, glNormalized });
	Stride += typeSize*count;
}
