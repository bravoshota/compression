#include "arithmetic.h"
#include <limits>

void Arithmetic::compress(uint8_t *data, uint32_t size)
{
    // https://www.youtube.com/watch?v=-7i6HaYhyW4&index=52&list=PLE125425EC837021F

    if (!init(data, size))
        return;

    uint64_t whole = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1;
    uint64_t half  = whole >> 1;
    uint64_t quart = half >> 1;
    uint64_t c[256];
    uint64_t d[256];
    uint64_t weight[256] = {0};

    // initialize symbols
    for (uint32_t i = 0; i < size; ++i)
    {
        ++weight[data[i]];
    }

    // initialize bounds
    c[0] = 0;
    d[0] = weight[0];
    for (uint32_t i = 1; i < 256; ++i)
    {
        c[i] = d[i-1];
        d[i] = c[i] + weight[i];
    }

    uint64_t s = 0;
    uint64_t a = 0;
    uint64_t b = whole;

    for (uint32_t i = 0; i < size; ++i)
    {
        uint64_t w = b - a;
        b = a + w * d[data[i]] / size;
        a = a + w * c[data[i]] / size;

        while (a > half || b < half)
        {
            if (b < half)
            {
                addBit(false);
                for (uint64_t i = 0; i < s; ++i)
                    addBit(true);
                s = 0;
                a = a << 1;
                b = b << 1;
            }
            else if (a > half)
            {
                addBit(true);
                for (uint64_t i = 0; i < s; ++i)
                    addBit(false);
                s = 0;
                a = (a - half) << 1;
                b = (b - half) << 1;
            }
        }

        while (a > quart || b < 3*quart)
        {
            ++s;
            a = (a - quart) << 1;
            b = (b - quart) << 1;
        }
    }

    ++s;
    if (a <= quart)
    {
        addBit(false);
        for (uint64_t i = 0; i < s; ++i)
            addBit(true);
    }
    else
    {
        addBit(true);
        for (uint64_t i = 0; i < s; ++i)
            addBit(false);
    }
}
