#pragma once

#include "ICompression.h"

class Arithmetic : public ICompression
{
public:
    virtual ~Arithmetic() {}
    virtual void compress(uint8_t *data, uint32_t size) override final;
    virtual Type type() override final { return Type::ARITHMETIC; }
};
