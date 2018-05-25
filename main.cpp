#include <iostream>
#include <fstream>
#include "huffman.h"


#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

int main(int nargs, char **args)
{
    if (nargs < 2)
    {
        std::cout << "please pass the filename!" << std::endl;
        exit(0);
    }

    for (int i = 1; i < nargs; ++i)
    {
        std::cout << "opening file: \"" << args[i] << "\"";

        std::ifstream file(args[i], std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open())
        {
            std::streampos origSize = file.tellg();
            char *data = new char[origSize];
            file.seekg (0, std::ios::beg);
            file.read(data, origSize);
            file.close();
            std::cout << "... " << origSize << " bytes read" << std::endl;

            Huffman compression;
            compression.compress(reinterpret_cast<uint8_t *>(data), origSize);
            std::cout << "output size = " << compression.outputSize() << " bytes" << std::endl;
            std::cout << "compress ratio = " << 100 * compression.outputSize() / origSize << "%" << std::endl << std::endl;
        }
        else
        {
            std::cout << "... ERROR!" << std::endl;
        }
    }

    return 0;
}
