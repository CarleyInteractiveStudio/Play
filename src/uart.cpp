/**
 * @file uart.c
 * @brief Driver de puerto serie (UART) para el RK3128.
 */

#include "rk3128_regs.h"

#define UART0_BASE        0x20060000
#define UART_RBR          (UART0_BASE + 0x0000)
#define UART_THR          (UART0_BASE + 0x0000)
#define UART_LSR          (UART0_BASE + 0x0014)

extern "C" void uart_init(void)
{
    // Configurar baudios a 115200 (Asumiendo reloj UART de 24MHz)
    // 1. Configurar IOMUX para UART0
    RK_REG(GRF_BASE + 0x0014) |= (1 << 4) | (1 << 6);

    // 2. Configurar línea (8 bits, sin paridad, 1 stop)
    RK_REG(UART0_BASE + 0x000c) = 0x83; // DLAB = 1
    RK_REG(UART0_BASE + 0x0000) = 13;   // Divisor para 115200
    RK_REG(UART0_BASE + 0x0004) = 0x00;
    RK_REG(UART0_BASE + 0x000c) = 0x03; // DLAB = 0
}

void uart_putc(char c)
{
    // Esperar a que el transmisor esté vacío
    while(!(RK_REG(UART_LSR) & (1 << 5)));
    RK_REG(UART_THR) = c;
}

extern "C" void uart_print(const char* s)
{
    while(*s) uart_putc(*s++);
}
