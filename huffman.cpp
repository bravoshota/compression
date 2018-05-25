#include "huffman.h"
#include <algorithm>

namespace
{
struct Symbol
{
    Symbol(uint8_t symbol)
        : weight(0)
        , parent(nullptr)
        , symbol(symbol)
        , isLeaf(true)
    {}

    Symbol(Symbol *leftChild, Symbol *rightChild)
        : weight(leftChild->weight + rightChild->weight)
        , parent(nullptr)
        , symbol(0)
        , children()
        , isLeaf(false)
    {
        children[0] = leftChild;
        children[0]->parent = this;
        children[1] = rightChild;
        children[1]->parent = this;
    }

    uint8_t symbol;
    uint32_t weight;
    Symbol *parent;
    Symbol *children[2];
    bool isLeaf;
};
}

void Huffman::compress(uint8_t *data, uint32_t size)
{
    m_output.resize(0);

    if (data == nullptr)
        return;

    if (size == 0)
        return;

    // initialize symbols
    std::vector<Symbol *> symbols;
    symbols.resize(256);
    for (int i = 0; i < symbols.size(); ++i)
    {
        symbols[i] = new Symbol(i);
    }

    std::vector<Symbol *> allSymbols(symbols);
    allSymbols.reserve(2*symbols.size());

    for (uint32_t i = 0; i < size; ++i)
    {
        ++ symbols[data[i]]->weight;
    }

    // sort symbols by weight descending
    std::sort(symbols.begin(), symbols.end(), [](const Symbol *s1, const Symbol *s2){
        return s1->weight > s2->weight;
    });

    // while there are roots more than 1:
    while (symbols.size() > 1)
    {
        Symbol *newSymbol = new Symbol(symbols[symbols.size() - 2], symbols[symbols.size() - 1]);
        allSymbols.push_back(newSymbol);
        symbols.pop_back();
        symbols[symbols.size() - 1] = newSymbol;

        // move newSymbol to correct position
        for (int i = symbols.size() - 2; i >= 0; --i)
        {
            if (newSymbol->weight <= symbols[i]->weight)
                break;
            symbols[i+1] = symbols[i];
            symbols[i] = newSymbol;
        }
    }

//    int minDepth = 90;
//    int maxDepth = 0;
//    int minSymbol = -1;
//    int maxSymbol = -1;

//    for (int i = 0; i < 256; ++i)
//    {
//        Symbol*symbol = allSymbols[i];
//        int depth = 0;

//        while (true)
//        {
//            if (symbol->parent)
//            {
//                symbol = symbol->parent;
//                depth++;
//            }
//            else
//            {
//                break;
//            }
//        }

//        if (minDepth > depth)
//        {
//            minDepth = depth;
//            minSymbol = i;
//        }

//        if (maxDepth < depth)
//        {
//            maxDepth = depth;
//            maxSymbol = i;
//        }
//    }

    m_output.reserve(size);
    m_output.push_back(0);

    const uint8_t oneBit = 128;
    m_lastBit = 0;

    for (uint32_t i = 0; i < size; ++i)
    {
        Symbol*symbol = allSymbols[data[i]];

        while (true)
        {
            if (symbol->parent)
            {
                if (symbol->parent->children[0] != symbol)
                {
                    m_output.back() |= (oneBit >> m_lastBit);
                }

                ++m_lastBit;

                if (m_lastBit == 8)
                {
                    m_lastBit = 0;
                    m_output.push_back(0);
                }

                symbol = symbol->parent;
            }
            else
            {
                break;
            }
        }
    }

    --m_lastBit;
    if (m_lastBit == 255)
    {
        m_lastBit = 7;
        m_output.pop_back();
    }

    for (auto val : allSymbols)
        delete val;
}
