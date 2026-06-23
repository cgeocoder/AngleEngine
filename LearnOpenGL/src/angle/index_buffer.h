#pragma once

#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

#include <initializer_list>

class IndexBuffer {
private:
    unsigned int m_ID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* _Data, unsigned int _Length);
    IndexBuffer(const std::initializer_list<unsigned int>& _Data);

    void bind(void) const;
    void unbind(void) const;

    inline unsigned int get_count(void) const { return m_Count; }
};

#endif // !__INDEX_BUFFER_H__