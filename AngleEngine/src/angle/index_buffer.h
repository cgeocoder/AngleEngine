#pragma once

#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

#include <initializer_list>

// Класс индексов для VBO
class IndexBuffer {
private:
    unsigned int m_ID;
    unsigned int m_Count;

public:
    // @param _Data     - массив индексов типа unsigned int
    // @param _Length    - длинна массива
    IndexBuffer(const unsigned int* _Data, unsigned int _Length);

    // @param _Data     - std::initializer_list типа unsigned int
    IndexBuffer(const std::initializer_list<unsigned int>& _Data);

    void bind(void) const;
    void unbind(void) const;

    inline unsigned int get_count(void) const { return m_Count; }
};

#endif // !__INDEX_BUFFER_H__