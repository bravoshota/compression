#pragma once

#include "ICompression.h"

class Huffman : public ICompression
{
public:
    virtual ~Huffman() {}
    virtual void compress(uint8_t *data, uint32_t size) override final;
    virtual Type type() override final { return Type::HUFFMAN; }
};
