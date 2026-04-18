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

#define GICC_IAR             (GIC_CPU_BASE + 0x00C)
#define GICC_EOIR            (GIC_CPU_BASE + 0x010)

extern "C" void gic_handler(void)
{
    // 1. Obtener ID de la interrupción
    uint32_t iar = *(volatile uint32_t *)GICC_IAR;
    uint32_t irq_id = iar & 0x3FF;

    if(irq_id == 32) { // Ejemplo ID de Timer
        extern void kernel_timer_irq(void);
        kernel_timer_irq();
    }

    // 2. Notificar fin de interrupción
    *(volatile uint32_t *)GICC_EOIR = iar;
}
