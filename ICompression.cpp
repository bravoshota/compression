#include "ICompression.h"

bool ICompression::init(uint8_t *data, uint32_t size)
{
    m_output.resize(0);

    if (data == nullptr)
        return false;

    if (size == 0)
        return false;

    m_output.reserve(size);
    m_lastBit = 7;

    return true;
}

void ICompression::addBit(bool bit)
{
    ++m_lastBit;

    if (m_lastBit == 8)
    {
        m_lastBit = 0;
        m_output.push_back(0);
    }

    if (bit)
    {
        static const uint8_t oneBit = 128;
        m_output.back() |= (oneBit >> m_lastBit);
    }
}
