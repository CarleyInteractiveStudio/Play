#include "pmu_rk.h"
#include "rk3128_regs.h"

void pmu_enter_sleep(void)
{
    // 1. Apagar VOP
    // 2. Reducir frecuencia de APLL
}

void pmu_set_brightness(uint8_t level)
{
    // Control de registros de retroiluminación (si aplica)
}
