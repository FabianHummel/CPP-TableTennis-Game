#include "buffer.h"

Buffer::Buffer()
{
	m_buffer = (char*)malloc(128);
	m_size = 128;
	m_cursor = 0;
}

Buffer::Buffer(char *buffer, size_t size)
{
	m_buffer = buffer;
	m_size = size;
	m_cursor = 0;
}