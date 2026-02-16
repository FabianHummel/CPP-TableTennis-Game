#pragma once

#include "enet.h"
#include <cstring>

class Buffer
{
private:
    char* m_buffer;
    size_t m_size;
    size_t m_cursor;

public:
    explicit Buffer(const size_t size)
    {
        m_buffer = (char*)malloc(size);
        m_size = size;
        m_cursor = 0;
    }

    explicit Buffer(char* data, const size_t size)
    {
        m_buffer = data;
        m_size = size;
        m_cursor = 0;
    }

    char* read(const size_t size)
    {
        char* ret = m_buffer + m_cursor;
        m_cursor += size;
        return ret;
    }

    template <typename T>
    T read()
    {
        T* ret = (T*)read(sizeof(T));
        return *ret;
    }

    template <typename T>
    void write(const T& value)
    {
        while (m_cursor + sizeof(T) > m_size)
        {
            m_size *= 2;
            m_buffer = (char*)realloc(m_buffer, m_size);
        }

        memcpy(m_buffer + m_cursor, &value, sizeof(T));
        m_cursor += sizeof(T);
    }

    [[nodiscard]] const void* data() const
    {
        return m_buffer;
    }

    [[nodiscard]] size_t size() const
    {
        return m_cursor;
    }
};