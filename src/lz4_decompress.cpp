#include "lz4_decompress.h"

/**
 * @brief Implementación mínima de descompresión LZ4.
 * Optimizada para no usar memoria dinámica.
 */
int lz4_decompress(const uint8_t* source, uint8_t* dest, uint32_t source_size, uint32_t max_dest_size)
{
    const uint8_t* ip = source;
    uint8_t* op = dest;
    const uint8_t* const iend = source + source_size;
    uint8_t* const oend = dest + max_dest_size;

    while (ip < iend) {
        uint8_t token = *ip++;
        uint32_t length = token >> 4;

        if (length == 15) {
            uint8_t s;
            do { s = *ip++; length += s; } while (s == 255);
        }

        // Copiar literales
        for(uint32_t i = 0; i < length; i++) *op++ = *ip++;

        if (ip >= iend) break;

        // Copiar secuencias repetidas (Match)
        uint16_t offset = ip[0] | (ip[1] << 8); ip += 2;
        uint32_t match_len = token & 0x0F;

        if (match_len == 15) {
            uint8_t s;
            do { s = *ip++; match_len += s; } while (s == 255);
        }
        match_len += 4;

        uint8_t* ref = op - offset;
        for(uint32_t i = 0; i < match_len; i++) *op++ = *ref++;
    }

    return (int)(op - dest);
}
