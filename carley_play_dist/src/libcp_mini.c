/**
 * @file libcp_mini.c
 * @brief Runtime de C ultra-ligero para juegos .pg.
 */

#include <stddef.h>

void * memcpy(void * dest, const void * src, size_t n) {
    char * d = (char *)dest;
    const char * s = (const char *)src;
    while (n--) *d++ = *s++;
    return dest;
}

void * memset(void * s, int c, size_t n) {
    char * p = (char *)s;
    while (n--) *p++ = (char)c;
    return s;
}

// Implementación mínima de printf para UART
void cp_printf(const char* fmt, ...) {
    // Solo imprime strings simples por ahora para ahorrar espacio
    extern void uart_print(const char* s);
    uart_print(fmt);
}
