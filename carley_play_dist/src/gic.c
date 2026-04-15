#include "gic.h"

#define GICD_CTLR            (GIC_DIST_BASE + 0x000)
#define GICD_ISENABLER(n)    (GIC_DIST_BASE + 0x100 + (n) * 4)
#define GICC_CTLR            (GIC_CPU_BASE + 0x000)
#define GICC_PMR             (GIC_CPU_BASE + 0x004)

void gic_init(void)
{
    // 1. Inicializar Distribuidor
    *(volatile uint32_t *)GICD_CTLR = 0x1;

    // 2. Inicializar Interfaz de CPU
    *(volatile uint32_t *)GICC_PMR = 0xFF; // Aceptar todas las prioridades
    *(volatile uint32_t *)GICC_CTLR = 0x1;
}

void gic_enable_interrupt(uint32_t irq)
{
    uint32_t n = irq / 32;
    uint32_t bit = irq % 32;
    *(volatile uint32_t *)GICD_ISENABLER(n) = (1 << bit);
}
