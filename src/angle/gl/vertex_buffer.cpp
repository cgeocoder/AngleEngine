#include "vertex_buffer.h"
#include "errors.h"

VertexBuffer::VertexBuffer(const void* _Data, unsigned int _Size) {
    GL(glGenBuffers(1, &m_ID));
    GL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    GL(glBufferData(GL_ARRAY_BUFFER, _Size, _Data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GL(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::bind() const {
    GL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::unbind() const {
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}