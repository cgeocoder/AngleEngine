#pragma once

#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

class VertexBuffer {
private:
	unsigned int m_ID;

public:
	VertexBuffer(const void* _Data, unsigned int _Size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};

#endif // !__VERTEX_BUFFER_H__