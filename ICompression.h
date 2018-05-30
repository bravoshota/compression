#pragma once

#include <stdint.h>
#include <vector>

class ICompression
{
public:
    enum class Type
    {
        HUFFMAN = 0,
        ARITHMETIC = 1
    };
public:
    virtual ~ICompression() {}
    virtual void compress(uint8_t *data, uint32_t size) = 0;
    virtual Type type() = 0;
    const uint32_t outputSize() const { return m_output.size(); }
    const uint8_t *outputData() const { return m_output.data(); }

protected:
    bool init(uint8_t *data, uint32_t size);
    void addBit(bool bit);

private:
    std::vector<uint8_t> m_output;
    uint8_t m_lastBit;
};
