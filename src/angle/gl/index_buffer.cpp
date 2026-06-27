#include "index_buffer.h"
#include "errors.h"

IndexBuffer::IndexBuffer(const unsigned int* _Data, unsigned int _Length) : m_Count{ _Length } {
    GL(glGenBuffers(1, &m_ID));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));

    GL(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        m_Count * sizeof(unsigned int),
        (void*)_Data,
        GL_STATIC_DRAW
    ));
}

IndexBuffer::IndexBuffer(const std::initializer_list<unsigned int>& _Data) : m_Count{ (unsigned int)_Data.size()} {
    GL(glGenBuffers(1, &m_ID));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));

    GL(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        m_Count * sizeof(unsigned int),
        (void*)_Data.begin(),
        GL_STATIC_DRAW
    ));
}

void IndexBuffer::bind(void) const {
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::unbind(void) const {
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}